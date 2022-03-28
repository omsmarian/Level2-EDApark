#include "View.h"

View::View(MQTTClient* robot)
{
    this->ptr = robot;
    this->suscribeTo(this->names.getBatteryLevel());
    this->suscribeTo(this->names.getNMotorTemperature(1));
    this->suscribeTo(this->names.getNMotorTemperature(2));
    this->suscribeTo(this->names.getNMotorTemperature(3));
    this->suscribeTo(this->names.getNMotorTemperature(4));
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

const char* View::displayBattery()
{
    static const char *text;
    getDatafrom();
    if(!getEmpty())
    {
            text = TextFormat("Battery: %.2f%", 100 * (this->vectorToFloat()));
    }
    return text;
}
const char* View::displayM1Temp()
{

}
const char* View::displayM2Temp()
{

}
const char* View::displayM3Temp()
{

}
const char* View::displayM4Temp()
{

}

void View::displayAllData()
{
    
}