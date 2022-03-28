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
	DrawText("[W]", SCREENWIDTH / 2 - 55, SCREENHEIGHT / 2 - 35, 50, GRAY);
	DrawText("[S]", SCREENWIDTH / 2 - 50, SCREENHEIGHT / 2 + 20, 50, GRAY);
	DrawText("[A]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 + 20, 50, GRAY);
	DrawText("[D]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 + 20, 50, GRAY);
	DrawText("[E]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 - 35, 50, GRAY);
	DrawText("[Q]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 - 35, 50, GRAY);
	bool keyDown = false;
	float amperY = 0, amperX = 0, amperTurn = 0, amperStop = 0, amperDiagonal = 0;
	if (IsKeyDown(KEY_W))
	{
		DrawText("[W]", SCREENWIDTH / 2 - 55, SCREENHEIGHT / 2 - 35, 50, GREEN);
		amperY += 0.5;
		if (amperY < 3)
		{
			this->floatToVector(amperY);
			this->sendDataTo(this->names.getNMotorCurrentSet(1));
			this->sendDataTo(this->names.getNMotorCurrentSet(4));
			this->floatToVector(-amperY);
			this->sendDataTo(this->names.getNMotorCurrentSet(2));
			this->sendDataTo(this->names.getNMotorCurrentSet(3));
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_S))
	{
		DrawText("[S]", SCREENWIDTH / 2 - 50, SCREENHEIGHT / 2 + 20, 50, GREEN);
		amperY -= 0.5;
		if (amperY > -3)
		{
			this->floatToVector(amperY);
			this->sendDataTo(this->names.getNMotorCurrentSet(1));
			this->sendDataTo(this->names.getNMotorCurrentSet(4));
			this->floatToVector(-amperY);
			this->sendDataTo(this->names.getNMotorCurrentSet(2));
			this->sendDataTo(this->names.getNMotorCurrentSet(3));
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_D))
	{
		DrawText("[D]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 + 20, 50, GREEN);
		amperX += 0.5;
		if (amperX < 3)
		{
			this->floatToVector(-amperX);
			this->sendDataTo(this->names.getNMotorCurrentSet(1));
			this->sendDataTo(this->names.getNMotorCurrentSet(2));
			this->floatToVector(amperX);
			this->sendDataTo(this->names.getNMotorCurrentSet(3));
			this->sendDataTo(this->names.getNMotorCurrentSet(4));
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_A))
	{
		DrawText("[A]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 + 20, 50, GREEN);
		amperX -= 0.5;
		if (amperX > -3)
		{
			this->floatToVector(amperX);
			this->sendDataTo(this->names.getNMotorCurrentSet(3));
			this->sendDataTo(this->names.getNMotorCurrentSet(4));
			this->floatToVector(-amperX);
			this->sendDataTo(this->names.getNMotorCurrentSet(1));
			this->sendDataTo(this->names.getNMotorCurrentSet(2));
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_E))
	{
		DrawText("[E]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 - 35, 50, GREEN);
		amperTurn += 0.125;
		if (amperTurn < 3)
		{
			this->floatToVector(-amperTurn);
			this->sendDataTo(this->names.getNMotorCurrentSet(1));
			this->sendDataTo(this->names.getNMotorCurrentSet(2));
			this->sendDataTo(this->names.getNMotorCurrentSet(3));
			this->sendDataTo(this->names.getNMotorCurrentSet(4));
		}
		keyDown = true;
	}
	if (IsKeyDown(KEY_Q))
	{
		DrawText("[Q]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 - 35, 50, GREEN);
		amperTurn -= 0.125;
		if (amperTurn > -3)
		{
			this->floatToVector(-amperTurn);
			this->sendDataTo(this->names.getNMotorCurrentSet(1));
			this->sendDataTo(this->names.getNMotorCurrentSet(2));
			this->sendDataTo(this->names.getNMotorCurrentSet(3));
			this->sendDataTo(this->names.getNMotorCurrentSet(4));
		}
		keyDown = true;
	}
	if (keyDown == false)
	{
		amperY = 0, amperTurn = 0, amperX = 0;
		this->floatToVector(amperStop);
		this->sendDataTo(this->names.getNMotorCurrentSet(1));
		this->sendDataTo(this->names.getNMotorCurrentSet(2));
		this->sendDataTo(this->names.getNMotorCurrentSet(3));
		this->sendDataTo(this->names.getNMotorCurrentSet(4));
	}
}

void Controller::suscribeTo(const std::string input)
{
	this->ptr->subscribe(input);
}