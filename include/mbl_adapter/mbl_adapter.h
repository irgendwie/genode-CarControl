#include <mosquittopp.h>
#include <libc/component.h>

class mbl_adapter : public mosqpp::mosquittopp
{
private:
	/* mosquitto */
	char host[16];
	const char* id = "mbl_adapter";
	const char* topic = "savm/car/0/+";
	int port;
	int keepalive;
	enum {
		PCT_OFF  = 0,
		PCT_STEP = 1,
		PCT_MIN  = 10,
		PCT_MAX  = 30,
	};
	float rpmMax = 0.0;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);

public:
	mbl_adapter(const char* id, Libc::Env &_env);
	~mbl_adapter();
};
