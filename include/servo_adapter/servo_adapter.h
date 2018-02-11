#include <mosquittopp.h>

class servo_adapter : public mosqpp::mosquittopp
{
private:
	/* mosquitto */
	char host[16];
	const char* id = "servo_adapter";
	const char* topic = "savm/car/0/+";
	int port;
	int keepalive;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);

	int transform_steer(float value);
	int transform_brake(float value);

	const static int SERVO_UPPER_BOUND = 7500;
	const static int SERVO_LOWER_BOUND = 4500;

public:
	servo_adapter(const char* id);
	~servo_adapter();
};
