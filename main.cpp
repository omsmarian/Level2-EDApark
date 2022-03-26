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
	Controller clase(&robot);

	const string batteryLevel = "robot1/power/batteryLevel";
	const string coordinates = "robot1/motion/position";
	const string velocity = "robot1/motion/velocity";
	const string motor1Setter = "robot1/motor1/current/set";
	const string motor3Setter = "robot1/motor3/current/set";
	robot.subscribe(batteryLevel);
	
	float amper = 6;
	float gonza = -6;
	clase.floatToVector(amper);
	clase.sendDatato(motor1Setter);
	clase.floatToVector(gonza);
	clase.sendDatato(motor3Setter);


	SetTargetFPS(60);
	while (!WindowShouldClose() && clase.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Anda A Laburar!", 340, 200, 20, LIGHTGRAY);
		if (!clase.getEmpty())
		
			cout << clase.vectorToFloat() << endl;
			//anda_a_la_mierda = lectura.data()->payload.data();
			//for (int i = 0; i < 3; i++)
				//cout << (*(float*)anda_a_la_mierda) << " ,";
			//cout << endl;
		

		EndDrawing();
	}
	CloseWindow();
}
