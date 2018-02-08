#include <savm/savm.h>
#include <base/log.h>
#include <util/xml_node.h>
#include <os/config.h>
#include <string.h>
#include <errno.h>

extern "C" {
#include <lwip/sockets.h>
}
#include <lwip/genode.h>

savm::savm()
{
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
			Genode::log((void *)strerror(errno));
		}
	} while(ret != MOSQ_ERR_SUCCESS);

	/* subscribe to topic */
	subscribe(NULL, topic);

	/* start blocking loop */
	loop_start();

	/*************************
	 ** Connection to SA/VM **
	 *************************/
	int sock;
	
	struct sockaddr_in srv_addr;
	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	srv_addr.sin_port = htons(9002);

	if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Genode::error("socket failed: ", (void *)strerror(errno));
	}

	if (lwip_connect(sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1) {
		Genode::error("connect failed: ", (void *)strerror(errno));
	}

	/* flow */
	int msg_len = 0;
	
}

void readAllBytes(void *buf, int socket, unsigned int size) {
	int offset = 0;
	int ret = lwip_read(socket, buf+offset, size);

	if (ret == -1) {
		Genode::error("lwip_read failed: ", (void *)strerror(errno));
	} else if (ret != size) {
		
	}
}

savm::~savm() {
}

void savm::on_message(const struct mosquitto_message *message)
{
	if (strstr(message->topic, "speed")) {
		/* TODO conversion + publish to mbl_client */
	} else {
		Genode::log("unknown topic: ", (void *)message->topic);
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
