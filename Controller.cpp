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

void Controller::keyboardInput()
{
	bool keyDown = false;
	float amper = 0, amper_w = 0, amper_a = 0, amper_s = 0, amper_d = 0;
	//float amper = amper_a + amper_s + amper_d + amper_w;
	if (IsKeyDown(KEY_W))
	{
		DrawText("[W]", SCREENWIDTH / 2 - 55, SCREENHEIGHT / 2 - 35, 50, GREEN);
		amper_w += 0.5;
		if (amper_w < 3)
		{
			this->floatToVector(amper_w);
			this->sendDataTo(this->names.getMotor1Setter());
			this->sendDataTo(this->names.getMotor4Setter());
			this->floatToVector(-amper_w);
			this->sendDataTo(this->names.getMotor2Setter());
			this->sendDataTo(this->names.getMotor3Setter());
		}
		keyDown = true;

	}
	if (IsKeyDown(KEY_D))
	{
		DrawText("[D]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 + 20, 50, GREEN);
		amper_d += 0.125;
		if (amper_d < 3)
		{
			this->floatToVector(-amper_d);
			this->sendDataTo(this->names.getMotor1Setter());
			this->sendDataTo(this->names.getMotor2Setter());
			this->sendDataTo(this->names.getMotor3Setter());
			this->sendDataTo(this->names.getMotor4Setter());
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_S))
	{
		DrawText("[S]", SCREENWIDTH / 2 - 50, SCREENHEIGHT / 2 + 20, 50, GREEN);
		amper_s += 0.5;
		if (amper_s < 3)
		{
			this->floatToVector(-amper_s);
			this->sendDataTo(this->names.getMotor1Setter());
			this->sendDataTo(this->names.getMotor4Setter());
			this->floatToVector(amper_s);
			this->sendDataTo(this->names.getMotor2Setter());
			this->sendDataTo(this->names.getMotor3Setter());
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_A))
	{
		DrawText("[A]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 + 20, 50, GREEN);
		amper_a += 0.125;
		if (amper_a < 3)
		{
			this->floatToVector(amper_a);
			this->sendDataTo(this->names.getMotor1Setter());
			this->sendDataTo(this->names.getMotor2Setter());
			this->sendDataTo(this->names.getMotor3Setter());
			this->sendDataTo(this->names.getMotor4Setter());
		}
		keyDown = true;
	}

}

void Controller::suscribeTo(const std::string input)
{
	this->ptr->subscribe(input);
}