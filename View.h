/*
 * View
 *
 * 22.08 EDA
 *
 * Grupo 12
 * Participants: Segundo Martinez Tanoira, Mariano Oms
 *
 * Level 2:
 *
 * This file contains the class resposible of displaying the data
 */

#ifndef VIEW_H
#define VIEW_H

#include"Controller.h"

#define SCREENWIDTH 450
#define SCREENHEIGHT 450

class View
{
public:

	View(MQTTClient* robot);
	void suscribeTo(const std::string input);
	void render2D();
	void displayVelocity();

private:

	float* vectorToFloat();
	bool getEmpty();
	void getDatafrom();
	const char* text;

	MQTTClient* client;
	std::vector<MQTTMessage> read;
	const std::string velocity = "robot1/motion/velocity";
};


#endif
