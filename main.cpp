/*
 * Controller
 *
 * 22.08 EDA
 *
 * Grupo 12
 * Participants: Segundo Martinez Tanoira, Mariano Oms
 *
 * Level 2:
 *
 * Main module
 */

#include <iostream>
#include "Controller.h"
#include "View.h"

using namespace std;

int main()
{
	MQTTClient robot(CLIENTNAME);
	Controller control(&robot);
	View render(&robot);

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "EDA controler");

	SetTargetFPS(60);
	while (!WindowShouldClose() && control.getIsConnected())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		control.keyboardInput();
		render.render2D();
		render.displayVelocity();
		EndDrawing();
	}
	CloseWindow();
}
