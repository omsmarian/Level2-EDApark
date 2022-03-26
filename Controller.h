#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MQTTClient.h"

#define POWER 6.0f

class Controller
{
public:
	Controller(MQTTClient* robot);
	void floatToVector(float num);
	void sendDatato(const std::string destination);
	void getDatafrom(const std::string source);
	float vectorToFloat();
	bool getIsConnected();
	bool getEmpty();

private:
	std::vector<char> write;
	std::vector<MQTTMessage> read;
	MQTTClient* ptr;
};



#endif
