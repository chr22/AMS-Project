/*
 * WeatherBalloonSensor.c
 *
 * Created: 04-03-2014 11:21:49
 *  Author: Nikolaj
 */ 

#define MEGA32_DEV True

#include "./Drivers/uart.h"
#define F_CPU 3686400


#include "./Drivers/BMP180.h"

#include <util/delay.h>
#include <avr/io.h>
//#include "Protocol/RadioSource.h"
#include "Drivers/uart.h"


int main(void)
{
	int err = 0;
	InitUART(9600, 8);
	//SendString("New Hello.");
	//SendChar(0x10);
	//SendChar(0x10);
	//SendChar(0x10);
	err = PerformFullTransmission(0x20, 2012, 2014, 3276);
	
	if(!(err < 0))
	{
		//SendString("DONE");
	}
	//return 1;
	while(1)
	{
		//SendString("Hello!");
		//TODO:: Please write your application code
	}
	
	return 1;
}