//#include "MQTTClient.h"
#include <iostream>
#include "raylib.h"
#include "Controller.h"

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "EDA controler");
	MQTTClient robot("controller");
	Controller control(&robot);

	const string batteryLevel = "robot1/power/batteryLevel";
	const string coordinates = "robot1/motion/position";
	const string velocity = "robot1/motion/velocity";
	const string motor1Setter = "robot1/motor1/current/set";
	const string motor2Setter = "robot1/motor2/current/set";
	const string motor3Setter = "robot1/motor3/current/set";
	const string motor4Setter = "robot1/motor4/current/set";
	robot.subscribe(batteryLevel);
	


	float amper = 0;
	bool keyDown = false;
	SetTargetFPS(60);
	while (!WindowShouldClose() && control.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Anda A Laburar!", 340, 200, 20, LIGHTGRAY);

 		if(IsKeyDown(KEY_W))
    		{
				amper += 1;
				if(amper < 10)
				{
    		    	control.floatToVector(amper);
					control.sendDataTo(motor1Setter);
					control.sendDataTo(motor4Setter);
					control.floatToVector(-amper);
					control.sendDataTo(motor2Setter);
					control.sendDataTo(motor3Setter);
				}
				keyDown = true;

    		}
    		if(IsKeyDown(KEY_D))
    		{
				amper +=1;
				if(amper < 10)
				{
			    	control.floatToVector(-amper);
					control.sendDataTo(motor1Setter);
    		    	control.sendDataTo(motor2Setter);
					control.sendDataTo(motor3Setter);
					control.sendDataTo(motor4Setter);
				}
				keyDown = true;
    		}
    		if(IsKeyDown(KEY_S))
    		{
				amper +=1;
				if(amper < 10)
				{
    		    	control.floatToVector(amper);
					control.sendDataTo(motor2Setter);
    		    	control.sendDataTo(motor3Setter);
					control.floatToVector(-amper);
					control.sendDataTo(motor1Setter);
					control.sendDataTo(motor4Setter);
				}
				keyDown = true;
    		}
    		if(IsKeyDown(KEY_A))
    		{
				amper += 1;
				if(amper < 10)
				{
			    	control.floatToVector(amper);
    		    	control.sendDataTo(motor1Setter);
					control.sendDataTo(motor2Setter);
					control.sendDataTo(motor3Setter);
					control.sendDataTo(motor4Setter);
				}
				keyDown = true;
    		}

			if(keyDown == false)
			{
				amper = 0;
				control.floatToVector(amper);
    			control.sendDataTo(motor1Setter);
				control.sendDataTo(motor2Setter);
				control.sendDataTo(motor3Setter);
				control.sendDataTo(motor4Setter);
			}
			keyDown = false;


		EndDrawing();
	}
	CloseWindow();
}
