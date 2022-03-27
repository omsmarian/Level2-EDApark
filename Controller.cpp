#include "Controller.h"

Controller::Controller(MQTTClient* robot)
{
	this->ptr = robot;
	ptr->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");
	this->write.resize(sizeof(float));
}

void Controller::floatToVector(float num)
{
	memcpy(this->write.data(), &num, sizeof(float));
}

void Controller::sendDataTo(const std::string destination)
{
	this->ptr->publish(destination, this->write);
}

float Controller::vectorToFloat()
{
	void* carrier = this->ptr->getMessages().data()->payload.data();				//SEGUN ACA ESTA EL PROBLEMA HAY Q HACER UNA FUNCION Q AGARRE EL MENSAJE
	return *(float*)carrier;														//Y OTRA Q LO CASTEE A CHAR PQ SINO SE ROMPE
}

bool Controller::getIsConnected()
{
	return this->ptr->isConnected();
}

bool Controller::getEmpty()
{
	return this->ptr->getMessages().empty();								// AHORA Q LO PIENSO ACA TMB PUEDE HABER PROBLEMA LA SOLUCION DEBE SER TENER UN VECTOR
}																			//DE LECTURA CREO PQ SINO HAY BARDO CON EL GETMESSAGE

void Controller::getDatafrom(const std::string source)
{
	//completar
}