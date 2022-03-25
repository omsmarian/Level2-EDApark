#include "MQTTClient.h"
#include <iostream>
#include "raylib.h"

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
	const string velocity = "robot1/motion/velocity";
	const string motor1Setter = "robot1/motor1/current/set";
	const string motor3Setter = "robot1/motor3/current/set";
	robot.subscribe(velocity);
	void* anda_a_la_mierda;

	vector<MQTTMessage> lectura;			// lo usamos para leer data
	
	float amper = 6;
	float gonza = -6;

	vector<char> copy(sizeof(float));
	memcpy(copy.data(), &amper, sizeof(float));
	robot.publish(motor1Setter, copy);
	memcpy(copy.data(), &gonza, sizeof(float));
	robot.publish(motor3Setter, copy);


	SetTargetFPS(60);
	while (!WindowShouldClose() && robot.isConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Anda A Laburar!", 340, 200, 20, LIGHTGRAY);
		lectura = robot.getMessages();
		if (!lectura.empty())
		{
			cout << "MIRA ACA" << endl;
			anda_a_la_mierda = lectura.data()->payload.data();
			for (int i = 0; i < 3; i++)
				cout << (*(float*)anda_a_la_mierda) << " ,";
			cout << endl;
		}

		EndDrawing();
	}
	CloseWindow();
}
