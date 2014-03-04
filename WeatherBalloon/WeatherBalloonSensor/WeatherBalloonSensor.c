/*
 * WeatherBalloonSensor.c
 *
 * Created: 04-03-2014 11:21:49
 *  Author: Nikolaj
 */ 


#include <avr/io.h>
#include "Drivers/uart.h"

int main(void)
{
	InitUART(9600,8);
	
    while(1)
    {
        //TODO:: Please write your application code 
		SendChar(ReadChar());
    }
}