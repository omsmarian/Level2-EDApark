#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MQTTClient.h"
#include "raylib.h"
#include "Topics.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 450
#define INTENSITY 4.0f

class Controller
{
public:
	Controller(MQTTClient* robot);
	bool getIsConnected();
	void keyboardInput();
	

private:
	void sendDataTo(const std::string destination, float power);
	void floatToVector(float num);

	
	std::vector<char> write;
	std::vector<char> check;
	MQTTClient* ptr;

	Topics names;
};



#endif
