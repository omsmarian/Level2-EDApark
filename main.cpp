#include "MQTTClient.h"
#include <iostream>
#include "raylib.h"

#define BETTERYLEVEL "robot/power/batteryLevel"

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "EDA controler");
	MQTTClient robot("controller");
	robot.connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");

	const string batteryLevel = "robot1/power/batteryLevel";
	const string coordinates = "robot1/motion/position";
	robot.subscribe(coordinates);
	void* anda_a_la_mierda;

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
			cout << "MIRA ACA" << endl;
			anda_a_la_mierda = messages.data()->payload.data();
			for(int i = 0; i < 3; i++)
				cout <<    (* (float*)anda_a_la_mierda) << ",";
			cout << endl;
		}

		EndDrawing();
	}
	CloseWindow();
}
