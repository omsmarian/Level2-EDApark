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
	void displayAllData();
	Image icon;

private:

	float* vectorToFloat();
	bool getEmpty();
	void getDatafrom();

	MQTTClient* ptr;
	std::vector<MQTTMessage> read;
	Topics names;
};


#endif
