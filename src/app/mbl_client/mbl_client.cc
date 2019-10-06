#include <mbl_client/mbl_client.h>
#include <base/log.h>
#include <util/xml_node.h>
#include <string.h>
#include <errno.h>
#include <ecu_api/Defines.h>
#include <base/attached_rom_dataspace.h>
#include <libc/component.h>

mbl_client::mbl_client(const char* id, Libc::Env &_env) : mosquittopp(id)
{
    	/* initialize roboteq core api */
	CoreAPI c_api(CONNECTION_COM);
    	_core = &c_api;

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

mbl_client::~mbl_client()
{
}

void mbl_client::on_message(const struct mosquitto_message *message)
{
	/* split type from topic */
	char *type = strrchr(message->topic, '/') + 1;
	/* get pointer to payload for convenience */
	char *value = (char *)message->payload;

	if (!strcmp(type, "powerpct")) {
		unsigned int powerpct = atoi(value);
        	_core->SetMotorSpeedAbs(powerpct);
	} else {
		Genode::log("unknown topic: ", (const char *)message->topic);
	}
}

void mbl_client::on_connect(int rc)
{
	Genode::log("connected to mosquitto server");
}

void mbl_client::on_disconnect(int rc)
{
	Genode::log("disconnect from mosquitto server");
}
