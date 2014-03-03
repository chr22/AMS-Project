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
#include "./HeaderFiles/MPL3115A2.h"

int main(void)
{
	//DDRD = 0b11000000;
	//DDRC = 0b1
	
	InitUART(9600, 8);
	SendString("Hej UART \r");
	
	MPL3115_init();
	
	unsigned long int val;
	
	while(1)
	{
		//val = MPL3115RegRead(0xF6);
			    //
		//SendString("Return: ");
		//SendChar((int)val);
		//
		
		SendString("Device id: ");
		SendInteger((int)MPL3115_GetDeviceId());
		SendString("\r\n");
		
		_delay_ms(300);
    }
	
	return 1;
}