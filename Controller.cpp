#include "Controller.h"

Controller::Controller(MQTTClient* robot)
{
	this->ptr = robot;
	ptr->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");
}

void Controller::floatToVector(float num)
{
	memcpy(this->write.data(), &num, sizeof(float));
}

void Controller::sendDatato(const std::string destination)
{
	this->ptr->publish(destination, this->write);
}

float Controller::vectorToFloat()
{
	void* carrier = this->ptr->getMessages().data()->payload.data();
	return *(float*)carrier;
}