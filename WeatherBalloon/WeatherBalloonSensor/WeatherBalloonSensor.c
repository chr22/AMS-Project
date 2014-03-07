/*
 * WeatherBalloonSensor.c
 *
 * Created: 04-03-2014 11:21:49
 *  Author: Nikolaj
 */ 

//#undef MEGA32_DEV
//#define MEGA32_DEV True

#include "./Drivers/uart.h"
//#define F_CPU 3686400

#define F_CPU 16000000

//#include "./Drivers/BMP180.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Protocol/RadioSource.h"

int main(void)
{
	//sei();
	
	int err = 0;
	
	InitUART(9600, 8);
		
 	while (1)
 	{
		err = PerformFullTransmission(0x20, 33, 22, 11);	
 		_delay_ms(3000);
 	}
	
	return 1;
}

