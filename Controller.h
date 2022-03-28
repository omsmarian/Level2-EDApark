#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MQTTClient.h"
#include "raylib.h"
#include "Topics.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 450

class Controller
{
public:
	Controller(MQTTClient* robot);
	void floatToVector(float num);
	void sendDataTo(const std::string destination);
	void getDatafrom(const std::string source);
	float vectorToFloat();
	bool getIsConnected();
	bool getEmpty();
	void keyboardInput();
	void suscribeTo(const std::string input);

private:
	std::vector<char> write;
	std::vector<MQTTMessage> read;
	MQTTClient* ptr;

	Topics names;
};



#endif
