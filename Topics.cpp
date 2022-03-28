#include "Topics.h"

std::string Topics::getBatteryLevel()
{
	return this->batteryLevel;
}
std::string Topics::getCoordinates()
{
    return this->coordinates;
}

std::string Topics::getNMotorCurrentSet(int x)
{
	return "robot1/motor" + std::to_string(x) + "/current/set";
}

std::string Topics::getNMotorTemperature(int x)
{
	return "robot1/motor" + std::to_string(x) + "/temperature";
}