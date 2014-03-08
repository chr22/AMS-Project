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

const unsigned char DeviceId;

int main(void)
{		
	InitUART(9600, 8);
	_delay_ms(50);
	
	BMP180_Init();

	DeviceId = BMP180_GetDeviceId();
		
	while (1)
	{
		PerformFullTransmission(DeviceId, BMP180_GetTemperature(), BMP180_GetAltitude(), BMP180_GetPressure(), BMP180_GetDeltaAltitude());
		_delay_ms(5000);
	}
	
	return 1;
}

