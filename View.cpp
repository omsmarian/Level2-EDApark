#include "View.h"

View::View(MQTTClient* robot)
{
	this->ptr = robot;
	this->suscribeTo(this->names.getVelocity());
	this->icon = LoadImage(".//icon.png");
}

float* View::vectorToFloat()
{
	void* carrier = this->read.data()->payload.data();
	return (float*)carrier;
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

void View::displayAllData()
{
	DrawText("[W]", SCREENWIDTH / 2 - 52, SCREENHEIGHT / 2 - 35, 50, GRAY);
	DrawText("[S]", SCREENWIDTH / 2 - 50, SCREENHEIGHT / 2 + 20, 50, GRAY);
	DrawText("[A]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 + 20, 50, GRAY);
	DrawText("[D]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 + 20, 50, GRAY);
	DrawText("[E]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 - 35, 50, GRAY);
	DrawText("[Q]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 - 35, 50, GRAY);
	if (IsKeyDown(KEY_W))
		DrawText("[W]", SCREENWIDTH / 2 - 52, SCREENHEIGHT / 2 - 35, 50, GREEN);
	if (IsKeyDown(KEY_S))
		DrawText("[S]", SCREENWIDTH / 2 - 50, SCREENHEIGHT / 2 + 20, 50, GREEN);
	if (IsKeyDown(KEY_A))
		DrawText("[A]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 + 20, 50, GREEN);
	if (IsKeyDown(KEY_D))
		DrawText("[D]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 + 20, 50, GREEN);
	if (IsKeyDown(KEY_Q))
		DrawText("[Q]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 - 35, 50, GREEN);
	if (IsKeyDown(KEY_E))
		DrawText("[E]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 - 35, 50, GREEN);

	static const char* text;
	getDatafrom();
	if (!getEmpty())
	{
		float* ptr = (this->vectorToFloat());
		float x = *ptr, y = *(ptr + 1), z = *(ptr + 2);
		float vel = sqrt(x * x + y * y + z * z);
		text = TextFormat("Velocity:\n%.2f m/s", vel);
	}
	DrawText(text, SCREENWIDTH / 2 - 60, 0, 20, RED);
}
