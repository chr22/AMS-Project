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
#include "Util/GlobalDefines.h"


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
	//tmpMeasureStruct.cmd = TEMP_CMD;
	//tmpMeasureStruct.tempValue = 124531;
		//
	//SendToDisplay(&tmpMeasureStruct);
	
	while(1)
	{

	}
}

ISR(USART_RXC_vect)
{
	//LCDDispChar(UDR);
	HandleIncoming(UDR);
}