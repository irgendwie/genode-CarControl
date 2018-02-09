#include <savm/savm.h>
#include <base/log.h>
#include <util/xml_node.h>
#include <os/config.h>
#include <string.h>
#include <errno.h>
#include <timer_session/connection.h>

/* fix redefinition of struct timeval */
#define timeval _timeval

extern "C" {
#include <lwip/sockets.h>
}
#include <lwip/genode.h>

void savm::readAllBytes(void *buf, int socket, unsigned int size) {
	int offset = 0;
	int ret = 0;

	do {
		ret = lwip_read(socket, buf + offset, size - offset);
		if (ret == -1) {
			Genode::error("lwip_read failed: ", (const char *)strerror(errno));
		} else {
			offset += ret;
		}
	} while(offset != size);
}

savm::savm(const char *id) : mosquittopp(id)
{
	sem_init(&allValSem, 0, 0);
	mosqpp::lib_init();  /* initialize mosquitto library */

	/* configure mosquitto library */
	Genode::Xml_node mosquitto = Genode::config()->xml_node().sub_node("mosquitto");
	try {
		mosquitto.attribute("ip-address").value(this->host, sizeof(host));
	} catch(Genode::Xml_node::Nonexistent_attribute) {
		Genode::error("mosquitto ip-address is missing from config");
	}
	this->port = mosquitto.attribute_value<unsigned int>("port", 1883);
	this->keepalive = mosquitto.attribute_value<unsigned int>("keepalive", 60);

	/* connect to mosquitto server */
	int ret;
	do {
		ret = connect(host, port, keepalive);
		switch(ret) {
		case MOSQ_ERR_INVAL:
			Genode::error("invalid parameter for mosquitto connect");
			return;
		case MOSQ_ERR_ERRNO:
			Genode::log("mosquitto ", (const char *)strerror(errno));
		}
	} while(ret != MOSQ_ERR_SUCCESS);

	/* subscribe to topic */
	subscribe(NULL, topic);

	/* start non-blocking mosquitto loop */
	loop_start();

	/***********************
	 ** Connection to SD2 **
	 ***********************/
	Timer::Connection timer;

	int sock;
	
	struct sockaddr_in srv_addr;
	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("10.200.40.10");
	srv_addr.sin_port = htons(9002);

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Genode::error("socket failed: ", (const char *)strerror(errno));
	}

	while((ret = lwip_connect(sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)) {
		Genode::error("connect failed: ", (const char *)strerror(errno));
		timer.msleep(1000);
		lwip_close(sock);
		if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			Genode::error("socket failed: ", (const char *)strerror(errno));
		}
	}

	/******************
	 ** Message flow **
	 ******************/
	protobuf::SensorDataOut sdo;
	protobuf::SensorDataOut_vec2 vec2;
	char val[512];
	int num = 0;
	while(true) {
		uint32_t msg_len;
		readAllBytes(&msg_len, sock, sizeof(msg_len));
		msg_len = ntohl(msg_len);

		char buffer[msg_len] = { '\0' };
		readAllBytes(buffer, sock, msg_len);

		/*******************
		 ** SensorDataOut **
		 *******************/
		sdo.ParseFromArray(buffer, msg_len);

		snprintf(val, sizeof(val), "%d", sdo.ispositiontracked());
		myPublish("isPositionTracked", val);
		
		snprintf(val, sizeof(val), "%d", sdo.isspeedtracked());
		myPublish("isSpeedTracked", val);
		
		vec2 = sdo.leadpos();
		snprintf(val, sizeof(val), "%f,%f", vec2.x(), vec2.y());
		myPublish("leadPos", val);

		vec2 = sdo.ownpos();
		snprintf(val, sizeof(val), "%f,%f", vec2.x(), vec2.y());
		myPublish("ownPos", val);

		vec2 = sdo.cornerfrontright();
		snprintf(val, sizeof(val), "%f,%f", vec2.x(), vec2.y());
		myPublish("cornerFrontRight", val);

		vec2 = sdo.cornerfrontleft();
		snprintf(val, sizeof(val), "%f,%f", vec2.x(), vec2.y());
		myPublish("cornerFrontLeft", val);

		vec2 = sdo.cornerrearright();
		snprintf(val, sizeof(val), "%f,%f", vec2.x(), vec2.y());
		myPublish("cornerRearRight", val);

		vec2 = sdo.cornerrearleft();
		snprintf(val, sizeof(val), "%f,%f", vec2.x(), vec2.y());
		myPublish("cornerRearLeft", val);

		snprintf(val, sizeof(val), "%f", sdo.leadspeed());
		myPublish("leadSpeed", val);

		snprintf(val, sizeof(val), "%f", sdo.ownspeed());
		myPublish("ownSpeed", val);

		snprintf(val, sizeof(val), "%d", sdo.curgear());
		myPublish("curGear", val);

		snprintf(val, sizeof(val), "%f", sdo.steerlock());
		myPublish("steerLock", val);

		snprintf(val, sizeof(val), "%f", sdo.enginerpm());
		myPublish("enginerpm", val);

		snprintf(val, sizeof(val), "%f", sdo.enginerpmmax());
		myPublish("enginerpmMax", val);

		snprintf(val, sizeof(val), "%f", sdo.steer());
		myPublish("steer", val);

		/*******************
		 ** CommandDataIn **
		 *******************/
		/* wait for data */
		sem_wait(&allValSem);

		msg_len = 0;
		std::string cdi_str;
		cdi.SerializeToString(&cdi_str);
		msg_len = htonl(cdi_str.size());

		int ret = lwip_write(sock, &msg_len, sizeof(msg_len));
		msg_len = ntohl(msg_len);
		if (ret == -1) {
			Genode::error("write length failed! %s", (const char *)strerror(errno));
		} else if (ret != sizeof(msg_len)) {
			Genode::error("write length failed to send complete message! ",
						  ret,
						  " vs. ",
						  sizeof(msg_len));
		}

		ret = lwip_write(sock, cdi_str.c_str(), msg_len);
		if (ret == -1) {
			Genode::error("write cdi failed! ", (const char *)strerror(errno));
		} else if (ret != msg_len) {
			Genode::error("write cdi failed to send complete message! ",
						  ret,
						  " vs. ",
						  msg_len);
		}

		num++;
		Genode::log("successful loop number: ", num);
	}
}

void savm::myPublish(char *type, char *value) {
	char topic[1024];
	strcpy(topic, "savm/car/0/");
	strncat(topic, type, sizeof(topic));
	publish(NULL, topic, strlen(value), value);
}

savm::~savm() {
}

void savm::on_message(const struct mosquitto_message *message)
{
	char *type = strrchr(message->topic, '/');
	char *value = (char *)message->payload;

	if (strcmp(type, "steer")) {
		cdi.set_steer(atof(value));
	} else if (strcmp(type, "accel")) {
		cdi.set_accel(atof(value));
	} else if (strcmp(type, "brakeFL")) {
		cdi.set_brakefl(atof(value));
	} else if (strcmp(type, "brakeFR")) {
		cdi.set_brakefr(atof(value));
	} else if (strcmp(type, "brakeRL")) {
		cdi.set_brakerl(atof(value));
	} else if (strcmp(type, "brakeRR")) {
		cdi.set_brakerr(atof(value));
	} else if (strcmp(type, "gear")) {
		cdi.set_gear(atoi(value));
	} else {
		Genode::log("unknown topic: ", (const char *)message->topic);
		return;
	}

	allValues = (allValues + 1) % 7;
	if (!allValues) {
		sem_post(&allValSem);
	}
}

void savm::on_connect(int rc)
{
	Genode::log("connected to mosquitto server");
}

void savm::on_disconnect(int rc)
{
	Genode::log("disconnect from mosquitto server");
}
