#include <mosquittopp.h>
#include <servo_controller_session/connection.h>

class servo_client : public mosqpp::mosquittopp
{
private:
	/* mosquitto */
	char host[16];
	const char* id = "servo_client";
	const char* topic = "rcar/control/motor/#";
	int port;
	int keepalive;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);

	const unsigned int STEER_CHANNEL = 6;
	const unsigned int BRAKE_LEFT_FRONT_CHANNEL = 1;
	const unsigned int BRAKE_RIGHT_FRONT_CHANNEL = 2;
	const unsigned int BRAKE_REAR_CHANNEL = 0;

	Servo_Controller::Connection servo_controller;

public:
	servo_client(const char* id);
	~servo_client();
};
