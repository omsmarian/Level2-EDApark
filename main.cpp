#include <iostream>
#include "Controller.h"
#include "View.h"

using namespace std;

int main()
{
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "EDA controler");
	MQTTClient robot("controller");
	Controller control(&robot);
	View Render(&robot);



	SetTargetFPS(60);
	while (!WindowShouldClose() && control.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		control.keyboardInput();
		//Render.displayAllData();
		EndDrawing();
	}
	CloseWindow();
}
