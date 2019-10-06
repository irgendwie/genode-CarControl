#include <servo_adapter/servo_adapter.h>
#include <base/log.h>
#include <util/xml_node.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <base/attached_rom_dataspace.h>
#include <libc/component.h>


servo_adapter::servo_adapter(const char* id, Libc::Env &_env) : mosquittopp(id)
{
	this->rbrake = 0;
	
	mosqpp::lib_init();  /* initialize mosquitto library */

	/* configure mosquitto library */
	Genode::Attached_rom_dataspace _config(_env, "config");
	/* get config */
	Genode::Xml_node mosquitto = _config.xml().sub_node("mosquitto");
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
		ret = this->connect(host, port, keepalive);
		switch(ret) {
		case MOSQ_ERR_INVAL:
			Genode::error("invalid parameter for mosquitto connect");
			return;
		case MOSQ_ERR_ERRNO:
			break;
			Genode::log("mosquitto ", (const char *)strerror(errno));
		}
	} while(ret != MOSQ_ERR_SUCCESS);

	/* subscribe to topic */
	do {
		ret = this->subscribe(NULL, topic);
		switch(ret) {
		case MOSQ_ERR_INVAL:
			Genode::error("invalid parameter for mosquitto subscribe");
			return;
		case MOSQ_ERR_NOMEM:
			Genode::error("out of memory condition occurred");
			return;
		case MOSQ_ERR_NO_CONN:
			Genode::error("not connected to a broker");
			return;
		}
	} while(ret != MOSQ_ERR_SUCCESS);

	/* start blocking loop */
	loop_forever();
}

servo_adapter::~servo_adapter()
{
}

int servo_adapter::transform_steer(float value)
{
    if (value < -1 || value > 1) {
		Genode::error("invalid steering angle - range is -1 to 1");
        return -1;
    }

    // Invert value as SpeedDreams thinks -1 is right
    value = -value;

    value = (value + 1)/2;
    return (SERVO_UPPER_BOUND - SERVO_LOWER_BOUND) * value + SERVO_LOWER_BOUND;
}

int servo_adapter::transform_brake(float value)
{
    if (value < 0 || value > 1) {
		Genode::error("invalid target brake position - range is 0 to 1");
        return -1;
    }

    return (SERVO_UPPER_BOUND - SERVO_LOWER_BOUND) * value + SERVO_LOWER_BOUND;
}

void servo_adapter::on_message(const struct mosquitto_message *message)
{
	/* split type from topic */
	char *type = strrchr(message->topic, '/') + 1;
	/* get pointer to payload for convenience */
	char *value = (char *)message->payload;

	char buffer[64];

	if (!strcmp(type, "steer")) {
		float steer = atof(value);
		snprintf(buffer, sizeof(buffer), "%d", transform_steer(steer));
		publish(NULL, "rcar/control/servo/steer", strlen(buffer), buffer);
	} else if (!strcmp(type, "brakeFL")) {
		float brakeFL = atof(value);
		snprintf(buffer, sizeof(buffer), "%d", transform_brake(brakeFL));
		publish(NULL, "rcar/control/servo/brake/fl", strlen(buffer), buffer);
	} else if (!strcmp(type, "brakeFR")) {
		float brakeFR = atof(value);
		snprintf(buffer, sizeof(buffer), "%d", transform_brake(brakeFR));
		publish(NULL, "rcar/control/servo/brake/fr", strlen(buffer), buffer);
	} else if (!strcmp(type, "brakeRL")) {
		brakeRL = atof(value);
		rbrake++;
	} else if (!strcmp(type, "brakeRR")) {
		brakeRR = atof(value);
		rbrake++;
	} else {
	  //Genode::log("unknown topic: ", (const char *)message->topic);
	}

	/* check if we got both values for the brake */
	if (rbrake == 2) {
		snprintf(buffer, sizeof(buffer), "%d", transform_brake((brakeRL + brakeRR) / 2));
		publish(NULL, "rcar/control/servo/brake/r", strlen(buffer), buffer);
		rbrake = 0;
	}
}

void servo_adapter::on_connect(int rc)
{
	Genode::log("connected to mosquitto server");
}

void servo_adapter::on_disconnect(int rc)
{
	Genode::log("disconnect from mosquitto server");
}
