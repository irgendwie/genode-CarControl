#include <mosquittopp.h>
#include <ecu_api/CoreAPI.h>
#include <libc/component.h>

class mbl_client : public mosqpp::mosquittopp
{
private:
	/* mosquitto */
	char host[16];
	const char* id = "mbl_client";
	const char* topic = "rcar/control/motor/+";
	int port;
	int keepalive;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);

        CoreAPI * _core;

public:
	mbl_client(const char* id, Libc::Env &_env);
	~mbl_client();
};
