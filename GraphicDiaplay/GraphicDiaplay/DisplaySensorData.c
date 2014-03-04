/*
 * DisplaySensorData.c
 *
 * Created: 04-03-2014 10:30:11
 *  Author: Christian
 */ 

#include "DisplayWrapper.h"


void WriteTemp(char* tempStr)
{
	WriteToDisplay("TEMP: ");
	WriteToDisplay(tempStr);
	WriteToDisplay("*");
	NewLine();
}

void WritePressure(char* presStr)
{
	WriteToDisplay("PRES: ");
	WriteToDisplay(presStr);
	WriteToDisplay("hPa");
	NewLine();
}

void WriteAltitude(char* altStr)
{
	WriteToDisplay("ALT:  ");
	WriteToDisplay(altStr);
	WriteToDisplay("m");
	NewLine();
}

void WriteSensorData(char* tempStr, char* presStr, char* altStr)
{
	WriteTemp(tempStr);
	WritePressure(presStr);
	WriteAltitude(altStr);
}