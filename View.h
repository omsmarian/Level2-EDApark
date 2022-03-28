#ifndef VIEW_H
#define VIEW_H

#include"Controller.h"
#include "Topics.h"

class View
{
public:

	View(MQTTClient* robot);
	void suscribeTo(const std::string input);
	const char* displayBattery();
	const char* displayM1Temp();
	const char* displayM2Temp();
	const char* displayM3Temp();
	const char* displayM4Temp();
	void displayAllData();

private:

	float vectorToFloat();
	bool getEmpty();
	void getDatafrom();

	MQTTClient* ptr;
	std::vector<MQTTMessage> read;
	Topics names;
};


#endif
