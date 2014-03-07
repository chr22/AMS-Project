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


int main(void)
{
	//sei();
	
	int err = 0;
	
	InitUART(9600, 8);
		
	//SendString("New Hello.");
	
 	while (1)
 	{
		err = PerformFullTransmission(0x20, 11, 22, 33);	
		//err = PerformFullTransmission(0x20, 2012, 2014, 3276);	
		//err = PerformFullTransmission(0x20, 2012, 2014, 3276);	
 		_delay_ms(3000);
 	}
	
	return 1;
}

ISR(TIMER1_OVF_vect)
{
	
	
}