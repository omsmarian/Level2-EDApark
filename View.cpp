/*
 * View
 *
 * 22.08 EDA
 *
 * Grupo 12
 * Participants: Segundo Martinez Tanoira, Mariano Oms
 *
 * Level 2:
 *
 * This file is responsible of displaying the data
 */

#include "View.h"

/*
 * Subscribes to the topic
 * INPUT: pointer to the client
 */
View::View(MQTTClient* robot)
{
	this->client = robot;
	this->suscribeTo(this->velocity);
}

/*
 * Converts a vector<char> into a float pointer
 * OUTPUT: a pointer to a float
 */
float* View::vectorToFloat()
{
	void* carrier = this->read.data()->payload.data();
	return (float*)carrier;
}

/*
 * Checks is the message is empty
 * OUTPUT: returns a 1 if the message is empty or a 0 if not
 */
bool View::getEmpty()
{
	return this->read.empty();
}

/*
 * Gets the messages and saves them in read
 */
void View::getDatafrom()
{
	this->read = this->client->getMessages();
}

/*
 * Subscribes to a topicc
 * INPUT: string with the directoin of topic
 */
void View::suscribeTo(const std::string input)
{
	this->client->subscribe(input);
}
/*
 * Draw the keys and changes color when the key is pressed 
 */
void View::render2D()
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
}

/*
 * Draw the velocity in the display 
 */
void View::displayVelocity()
{
	static const char* previousVelocity;
	getDatafrom();
	if (!getEmpty())
	{
		float* ptr = (this->vectorToFloat());
		float x = *ptr, y = *(ptr + 1), z = *(ptr + 2);
		float vel = sqrt(x * x + y * y + z * z);
		previousVelocity = TextFormat("Velocity:\n%.2f m/s", vel);
	}
	DrawText(previousVelocity, SCREENWIDTH / 2 - 60, 0, 20, RED);
}
