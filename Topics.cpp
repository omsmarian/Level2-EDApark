#include "Topics.h"

std::string Topics::getNMotorCurrentWriter(int x)
{
	return "robot1/motor" + std::to_string(x) + "/current/set";
}

std::string Topics::getVelocity()
{
	return this->velocity;
}