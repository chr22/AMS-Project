/*
 * Hello_LM3115_ATMega32.c
 *
 * Created: 25-02-2014 09:17:22
 *  Author: Casper
 */ 
#define F_CPU 3686400

#include <avr/io.h>
#include <util/delay.h>
#include "./HeaderFiles/uart.h"
#include "./HeaderFiles/BMP180.h"

int main(void)
{
	//DDRD = 0b11000000;
	//DDRC = 0b1
	
	InitUART(9600, 8);
	
	SendString("Hej UART \r\n");
	
	BMP180_Init();
	
	while(1)
	{	
		SendString("Device id: ");
		SendInteger((int)BMP180_GetDeviceId());
		SendString("\r\n \r\n");
		
		SendString("Temperature: ");
		SendInteger(BMP180_GetTemperature());
		
		SendString("\r\n-----------------\r\n");
		
		_delay_ms(1000);
    }
	
	return 1;
}