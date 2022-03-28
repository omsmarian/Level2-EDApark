//#include "MQTTClient.h"
#include <iostream>
#include "Controller.h"

using namespace std;

int main()
{
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "EDA controler");
	MQTTClient robot("controller");
	Controller control(&robot);

	//control.suscribeTo();



	SetTargetFPS(60);
	while (!WindowShouldClose() && control.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("[W]", SCREENWIDTH / 2 - 55, SCREENHEIGHT / 2 - 35, 50, GRAY);
		DrawText("[S]", SCREENWIDTH / 2 - 50, SCREENHEIGHT / 2 + 20, 50, GRAY);
		DrawText("[A]", SCREENWIDTH / 2 - 120, SCREENHEIGHT / 2 + 20, 50, GRAY);
		DrawText("[D]", SCREENWIDTH / 2 + 20, SCREENHEIGHT / 2 + 20, 50, GRAY);
		control.keyboardInput();
		EndDrawing();
	}
	CloseWindow();
}
