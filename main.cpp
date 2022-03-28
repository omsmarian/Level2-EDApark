//#include "MQTTClient.h"
#include <iostream>
#include "Controller.h"

using namespace std;

int main()
{
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "EDA controler");
	MQTTClient robot("controller");
	Controller control(&robot);




	SetTargetFPS(60);
	while (!WindowShouldClose() && control.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		control.keyboardInput();
		EndDrawing();
	}
	CloseWindow();
}
