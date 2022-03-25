#include "MQTTClient.h"
#include "raylib.h"
#include <iostream>

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "EDA controler");
	MQTTClient robot("controller");
	robot.connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");

	const string batteryLevel = "robot1/power/batteryLevel";
	robot.subscribe(batteryLevel);

	vector<MQTTMessage> messages;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Anda A Laburar!", 340, 200, 20, LIGHTGRAY);

		messages = robot.getMessages();
		if (messages.size())
		{
			for (int i = 0; i < messages.size(); i++)
			{
				cout << "MIRA ACA" << endl;
				cout << messages.data()->topic << endl;
			}
		}

		EndDrawing();
	}
	CloseWindow();
}
