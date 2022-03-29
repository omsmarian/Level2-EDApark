#include <iostream>
#include "Controller.h"
#include "View.h"

using namespace std;

int main()
{
	MQTTClient robot("controller");
	Controller control(&robot);
	View render(&robot);
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "EDA controler");
	SetWindowIcon(render.icon);						// TODO: hay un icono :0



	SetTargetFPS(60);
	while (!WindowShouldClose() && control.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		control.keyboardInput();
		render.displayAllData();
		EndDrawing();
	}
	CloseWindow();
}
