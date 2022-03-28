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
	bool getIsConnected();
	void keyboardInput();
	

private:
	void sendDataTo(const std::string destination);
	void floatToVector(float num);

	
	std::vector<char> write;
	MQTTClient* ptr;

	Topics names;
};



#endif
