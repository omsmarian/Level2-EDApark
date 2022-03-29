#include "Controller.h"

Controller::Controller(MQTTClient* robot)
{
	this->ptr = robot;
	ptr->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");
	this->write.resize(sizeof(float));
	this->amperYcheck = 0,this->amperXcheck = 0, this->amperRotCheck = 0;
}

void Controller::floatToVector(float num)
{
	memcpy(this->write.data(), &num, sizeof(float));
}

void Controller::sendDataTo(const std::string destination, float power)
{
	this->floatToVector(INTENSITY * power);
	this->ptr->publish(destination, this->write);
}

bool Controller::getIsConnected()
{
	return this->ptr->isConnected();
}


void Controller::keyboardInput()
{


	int amperY = IsKeyDown(KEY_W) - IsKeyDown(KEY_S), amperX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A),
		amperRot = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);
	if ((amperY != amperYcheck) || (amperX != amperXcheck) || (amperRot != amperRotCheck))
	{
		this->sendDataTo(this->names.getNMotorCurrentWriter(1), amperY - amperX - amperRot / 2.0f);
		this->sendDataTo(this->names.getNMotorCurrentWriter(2), -amperY - amperX - amperRot / 2.0f);
		this->sendDataTo(this->names.getNMotorCurrentWriter(3), -amperY + amperX - amperRot / 2.0f);
		this->sendDataTo(this->names.getNMotorCurrentWriter(4), amperY + amperX - amperRot / 2.0f);
	}
	this->amperYcheck = amperY,this->amperXcheck = amperX, this->amperRotCheck = amperRot;
}