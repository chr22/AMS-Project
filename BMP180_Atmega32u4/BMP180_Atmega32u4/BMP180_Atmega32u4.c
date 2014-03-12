/*
 * Hello_LM3115_ATMega32.c
 *
 * Created: 25-02-2014 09:17:22
 *  Author: Casper
 */ 
#include "./Util/GlobalDefines.h"

#include <avr/io.h>
#include <util/delay.h>
#include "./Drivers/uart.h"
#include "./Drivers/BMP180.h"

int main(void)
{
	InitUART(9600, 8);
	
	SendString("Hej UART \r\n");
	
	BMP180_Init(102600);
	
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