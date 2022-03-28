#include "Topics.h"

std::string Topics::getBatteryLevel()
{
	return this->batteryLevel;
}
std::string Topics::getPower()
{
    return this->power;
}

std::string Topics::getNMotorCurrentSet(int x)
{
	return "robot1/motor" + std::to_string(x) + "/current/set";
}

std::string Topics::getNMotorTemperature(int x)
{
	return "robot1/motor" + std::to_string(x) + "/temperature";
}