#ifndef TOPICS_H
#define TOPICS_H

#include <string>

class Topics
{
public:
	std::string getBatteryLevel();
	std::string getCoordinates();
	std::string getMotor1Setter();
	std::string getMotor2Setter();
	std::string getMotor3Setter();
	std::string getMotor4Setter();

private:
	const std::string batteryLevel = "robot1/power/batteryLevel";
	const std::string coordinates = "robot1/motion/position";
	const std::string velocity = "robot1/motion/velocity";
	const std::string motor1Setter = "robot1/motor1/current/set";
	const std::string motor2Setter = "robot1/motor2/current/set";
	const std::string motor3Setter = "robot1/motor3/current/set";
	const std::string motor4Setter = "robot1/motor4/current/set";
};

#endif
