/*
 * WeatherBalloonServer.c
 *
 * Created: 04-03-2014 11:20:39
 *  Author: Nikolaj
 */ 
#include <math.h>
#include <avr/io.h>

#include <avr/interrupt.h>
#include "Drivers/uart.h"
#include "Drivers/lcd162.h"
#include "Drivers/dem128064a.h"
#include "Wrappers/DisplaySensorData.h"
#include "Wrappers/DisplayWrapper.h"
#include "Protocol/ServerProtocol.h"

#include "../WeatherBalloonCommon/GlobalDefines.h"
#include "DefinesServer.h"


int main(void)
{
	//WriteTemp("123");
		
	//char k = 'b';
	InitUART(9600, 8);

	//LCDInit();
	//Enable receive-byte interrupt
	UCSRB |= (1 << RXCIE);
	//SendString("Hullo");
	//SendChar(0x50);
	//SendChar(0x50);
	//SendChar(0x50);
	
	//LCDDispString("Main");
	WriteToDisplay("Main");
	NewLine();
	sei();
	
	//MeasurementStruct tmpMeasureStruct;
	//
	//tmpMeasureStruct.sensorValues[0].cmd = TEMP_CMD;
	//tmpMeasureStruct.sensorValues[0].sensorValue = 1234;
	//
	//tmpMeasureStruct.sensorValues[1].cmd = DELALT_CMD;
	//tmpMeasureStruct.sensorValues[1].sensorValue = 7834;
	//
	//tmpMeasureStruct.sensorValues[2].cmd = PRES_CMD;
	//tmpMeasureStruct.sensorValues[2].sensorValue = 1846;
	//
	//tmpMeasureStruct.sensorValues[3].cmd = ALT_CMD;
	//tmpMeasureStruct.sensorValues[3].sensorValue = 4321;
	
	//SendToDisplay(&tmpMeasureStruct, 4);
	
	while(1)
	{

	}
}

ISR(USART_RXC_vect)
{
	int err = 0;
	
	err = HandleIncoming(UDR);
	
	if(err < 0)
	{
		WriteToDisplay("timeout");
	}
}