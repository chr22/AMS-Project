/*
 * WeatherBalloonSensor.c
 *
 * Created: 04-03-2014 11:21:49
 *  Author: Nikolaj
 */ 


#include <avr/io.h>
//#include "Protocol/RadioSource.h"
#include "Drivers/uart.h"


int main(void)
{
	int i = 0;
	InitUART(9600,8);
	//PerformFullTransmission(0x20,2730, 3003, 3276);
	//SendString("AHello.");
	//SendChar(0x10);
	SendChar(0x20);
    while(1)
    {
        //TODO:: Please write your application code 
		//SendChar(ReadChar());
		//SendInteger(i);
		//SendString("  ");
		++i;
    }
	return 1;
}