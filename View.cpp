#include "View.h"

View::View(MQTTClient* robot)
{
    this->ptr = robot;
    this->suscribeTo(this->names.getBatteryLevel());
}

bool View::getEmpty()
{
	return this->read.empty();
}

float View::vectorToFloat()
{
	void* carrier = this->read.data()->payload.data();
	return *(float*)carrier;
}

bool View::getEmpty()
{
	return this->read.empty();
}

void View::getDatafrom()
{
	this->read = this->ptr->getMessages();
}

void View::suscribeTo(const std::string input)
{
	this->ptr->subscribe(input);
}

void View::displayData()
{
    getDatafrom();
    if(!getEmpty())
    {
        if (read.data()->topic == this->names.getBatteryLevel())
        {
            const char *text = TextFormat("Battery: %03f", 100*(this->vectorToFloat()));
            DrawText(text,0,0,20,RED);
        }
    }
}