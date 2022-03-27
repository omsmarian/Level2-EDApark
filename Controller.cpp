#include "Controller.h"

Controller::Controller(MQTTClient* robot)
{
	this->ptr = robot;
	ptr->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");
	this->write.resize(sizeof(float));
}

void Controller::floatToVector(float num)
{
	memcpy(this->write.data(), &num, sizeof(float));
}

void Controller::sendDataTo(const std::string destination)
{
	this->ptr->publish(destination, this->write);
}

float Controller::vectorToFloat()
{
	void* carrier = this->read.data()->payload.data();
	return *(float*)carrier;
}

bool Controller::getIsConnected()
{
	return this->ptr->isConnected();
}

bool Controller::getEmpty()
{
	return this->read.empty();
}

void Controller::getDatafrom(const std::string source)
{
	this->read = this->ptr->getMessages();
}