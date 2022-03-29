/*
 * Controller
 *
 * 22.08 EDA
 *
 * Grupo 12
 * Participants: Segundo Martinez Tanoira, Mariano Oms
 *
 * Level 2:
 *
 * This file contains the class responsible for controlling the robot
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MQTTClient.h"
#include "raylib.h"

#define CLIENTNAME "controller"
#define IP "127.0.0.1"
#define PORT 1883
#define USERNAME "user"
#define PASSWORD "vdivEMMN3SQWX2Ez"
#define CURRENT 4.0f
#define SCALE_FACTOR 2.0f

class Controller
{
public:
	Controller(MQTTClient* robot);
	bool getIsConnected();
	void keyboardInput();


private:
	void sendCurrentToMotor(const std::string destination, float power);
	void floatToVector(float num);
	std::string motorNCurrentWriter(int x);

	std::vector<char> write;
	int previousAmperY;
	int previousAmperX;
	int previousAmperRot;
	MQTTClient* client;

};



#endif
