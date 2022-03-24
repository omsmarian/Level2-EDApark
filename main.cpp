#include "MQTTClient.h"
#include "raylib.h"
#include <iostream>

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "EDA controler");

	MQTTClient control("controller");
	control.connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");			// IMPORTANTE!!! PRIMERO HACER LO MONO DE LEER LOS DATOS
	cout << "conectado?" << endl;											// creo q con lo la linea 22 ahi recibo el dato pero no sé como imprimirlo
	cout << "0 no, 1 si" << endl;
	cout << "estado = " << control.isConnected() << endl;

	control.subscribe("power");											// capaz mejor hacer una clase q se suscriba y lea las cosas
	control.subscribe("batteryLevel");

	/* hacer función q printee los valores de un vector<MQTTMessage>
	seguramente hacer una clase q maneje todo esto
	deberia ser como un printf del topic y otro del payload */

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Anda Pibe!",
			340, 200, 20, LIGHTGRAY);
		vector<MQTTMessage> mensaje = control.getMessages();
		cout << mensaje.data()->topic << endl;
		EndDrawing();
	}
	CloseWindow();
}
