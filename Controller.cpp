/*
 * Controller
 *
 * 22.08 EDA
 *
 * Grupo 12
 * Participants: Segundo Martinez Tanoira, Mariano Oms
 *
 * Level 2:
 *
 * This file is responsible of recieve data from the keyboard and send it to EDApark
 */


#include "Controller.h"

 /*
  * Connects to MQTT server and initialize the objects
  * INPUT: Pointer to the client
  */
Controller::Controller(MQTTClient* robot)
{
	this->client = robot;
	client->connect(IP, PORT, USERNAME, PASSWORD);
	this->write.resize(sizeof(float));
	this->previousAmperY = 0, this->previousAmperX = 0, this->previousAmperRot = 0;
}

/*
 * Converts a float into a Vector<char> and saves it in write
 * INPUT: the number to convert
 */
void Controller::floatToVector(float num)
{
	memcpy(this->write.data(), &num, sizeof(float));
}
/*
 * Contorls the motros by current
 * INPUT: direction of the motor and the power that is going to be set in that motor
 */
void Controller::sendCurrentToMotor(const std::string destination, float power)
{
	this->floatToVector(CURRENT * power);
	this->client->publish(destination, this->write);
}
/*
 * Verifies if it is connect to MQTT server
 * OUTPUT: Returns a 1 if it connects to the server or a 0 if not
 */
bool Controller::getIsConnected()
{
	return this->client->isConnected();
}

/*
 *  Read the keyboard input and sets the motors
 */
void Controller::keyboardInput()
{
	int amperY = IsKeyDown(KEY_W) - IsKeyDown(KEY_S), amperX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A),
		amperRot = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);
	if ((amperY != previousAmperY) || (amperX != previousAmperX) || (amperRot != previousAmperRot))
	{
		this->sendCurrentToMotor(this->motorNCurrentWriter(1), amperY - amperX - amperRot / SCALE_FACTOR);
		this->sendCurrentToMotor(this->motorNCurrentWriter(2), -amperY - amperX - amperRot / SCALE_FACTOR);
		this->sendCurrentToMotor(this->motorNCurrentWriter(3), -amperY + amperX - amperRot / SCALE_FACTOR);
		this->sendCurrentToMotor(this->motorNCurrentWriter(4), amperY + amperX - amperRot / SCALE_FACTOR);
	}
	this->previousAmperY = amperY, this->previousAmperX = amperX, this->previousAmperRot = amperRot;
}
/*
 * Gets the topic of the motor
 * INPUT: The number of the motor
 * OUTPUT: String with the destination
 */
std::string Controller::motorNCurrentWriter(int x)
{
	return "robot1/motor" + std::to_string(x) + "/current/set";
}
