#ifndef VIEW_H
#define VIEW_H

#include"Controller.h"
#include "Topics.h"

class View
{
public:

	View(MQTTClient* robot);
	bool getEmpty();
	void suscribeTo(const std::string input);
    void displayData();

private:

	float vectorToFloat();
    bool getEmpty();
	void getDatafrom();

	MQTTClient* ptr;
	std::vector<MQTTMessage> read;
	Topics names;
};


#endif
