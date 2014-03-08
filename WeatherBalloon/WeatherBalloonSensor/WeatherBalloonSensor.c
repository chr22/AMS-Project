/*
* WeatherBalloonSensor.c
*
* Created: 04-03-2014 11:21:49
*  Author: Nikolaj
*/

#include "./Util/GlobalDefines.h"
#include "./Drivers/uart.h"


#include "./Drivers/BMP180.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Protocol/RadioSource.h"

int main(void)
{		
	InitUART(9600, 8);
	_delay_ms(50);
	
	BMP180_Init();
		
	while (1)
	{
		PerformFullTransmission(0x20, BMP180_GetTemperature(), BMP180_GetAltitude(), BMP180_GetPressure());
		_delay_ms(5000);
	}
	
	return 1;
}

