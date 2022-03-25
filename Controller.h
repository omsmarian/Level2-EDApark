#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MQTTClient.h"

class Controller
{
public:
	Controller(MQTTClient* robot);
	void floatToVector(float num);
	void sendDatato(const std::string destination);
	float vectorToFloat();


private:
	std::vector<char> write;
	std::vector<MQTTMessage> read;
	MQTTClient* ptr;
};



#endif
