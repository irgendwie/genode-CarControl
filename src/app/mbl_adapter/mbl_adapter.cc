#include <mbl_adapter/mbl_adapter.h>
#include <base/log.h>
#include <util/xml_node.h>
#include <os/config.h>
#include <string.h>
#include <errno.h>

mbl_adapter::mbl_adapter()
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
	loop_forever();
}

void mbl_adapter::on_message(const struct mosquitto_message *message)
{
	if (strstr(message->topic, "speed")) {
		/* TODO conversion + publish to mbl_client */
	} else {
		Genode::log("unknown topic: ", (void *)message->topic);
	}
}

void mbl_adapter::on_connect(int rc)
{
	Genode::log("connected to mosquitto server");
}

void mbl_adapter::on_disconnect(int rc)
{
	Genode::log("disconnect from mosquitto server");
}
