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


int main(void)
{
	int a = log(842)/log(2) + 1;
	
	
	InitUART(9600, 8);
	LCDInit();
	//LCDDispString("Hello World!");
	LCDDispInteger(a);
	
	
    while(1)
    {
        
    }
	return 0;
}

ISR(USART_RXC_vect)
{
	//HandleIncoming(UDR);
}