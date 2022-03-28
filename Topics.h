#ifndef TOPICS_H
#define TOPICS_H

#include <string>

#define MOTOR_CURRENT(x) ("robot1/motor"+ to_strng(x) + "/current/set")

class Topics
{
public:
	std::string getBatteryLevel();
	std::string getPower();
	std::string getNMotorCurrentSet(int x);
	std::string getNMotorTemperature(int x);

private:
	const std::string batteryLevel = "robot1/power/batteryLevel";
	const std::string power = "robot1/power/";
	const std::string velocity = "robot1/motion/velocity";
};

#endif
