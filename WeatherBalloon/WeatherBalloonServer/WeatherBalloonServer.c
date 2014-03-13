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
#include "Drivers/dem128064a.h"
#include "Wrappers/DisplaySensorData.h"
#include "Wrappers/DisplayWrapper.h"
#include "Protocol/ServerProtocol.h"

#include "../WeatherBalloonCommon/GlobalDefines.h"
#include "DefinesServer.h"


int main(void)
{
	InitUART(9600, 8);

	//Enable receive-byte interrupt
	UCSRB |= (1 << RXCIE);
		
	ClearScreen();
	
	sei();
	
	while(1){}
}

ISR(USART_RXC_vect)
{
	int err = 0;
	
	err = HandleIncoming(UDR);
	
	if(err < 0)
	{}
}