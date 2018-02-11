#include <mosquittopp.h>
#include <savm/SensorDataOut.pb.h>
#include <savm/CommandDataIn.pb.h>
#include <semaphore.h>

/* fix redefinition of struct timeval */
#define timeval _timeval

class savm : public mosqpp::mosquittopp
{
	private:
	/* mosquitto */
	char host[16];
	const char* id = "savm";
	const char* topic = "ecu/acc/#";
	int port;
	int keepalive;

	protobuf::CommandDataIn cdi;
	int allValues;
	sem_t allValSem;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);

	void readAllBytes(void *buf, int socket, unsigned int size);
	void myPublish(const char *type, const char *value);

	public:
	savm(const char* id);
	~savm();
};
