#include <mosquittopp.h>

class mbl_adapter : public mosqpp::mosquittopp
{
	private:
	/* mosquitto */
	char host[16];
	const char* id = "mbl_adapter";
	const char* topic = "simulation/car/1/#";
	int port;
	int keepalive;
	enum {
		VEL_OFF  = 0,
		VEL_STEP = 1,
		VEL_MIN  = 10,
		VEL_MAX  = 30,
	};

	mbl_adapter();
	~mbl_adapter();
	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);
};
