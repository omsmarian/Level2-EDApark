#ifndef TOPICS_H
#define TOPICS_H

#include <string>

class Topics
{
public:

	std::string getNMotorCurrentWriter(int x);
	std::string getVelocity();

private:

	const std::string velocity = "robot1/motion/velocity";
};

#endif
