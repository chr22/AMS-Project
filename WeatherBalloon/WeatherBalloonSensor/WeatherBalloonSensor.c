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
	InitUART(9600, 8);
	
	BMP180_Init();
	
		
    while(1)
    {
		SendString("\r\n--------------------------\r\n");
		SendString("Temperature in C: ");
		SendInteger((int)BMP180_GetTemperature()/10);
		SendString("\r\n");
		
		SendString("Pressure in hPa: ");
		SendInteger((int)(BMP180_GetPressure()/100));
		SendString("\r\n");
		
		SendString("Altitude in km: ");
		SendInteger((int)(BMP180_GetAltitude()));
		SendString("\r\n");
		
		SendString("\r\n");
	
		_delay_ms(1500);
    }
	return 1;
}