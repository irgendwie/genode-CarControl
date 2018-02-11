#include <mosquittopp.h>

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

public:
	mbl_client(const char* id);
	~mbl_client();
};
