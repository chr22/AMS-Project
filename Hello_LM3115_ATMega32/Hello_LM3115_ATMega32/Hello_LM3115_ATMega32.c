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
	SendString("Hej UART");
	
	MPL3115_init();
	
	unsigned char Address = 0;
	while(1)
	{	
		
	Address = MPL3115_GetDeviceId();
	    
    //TODO:: Please write your application code 
	SendString("Address: ");
	SendChar(Address);
		
	_delay_ms(1500);
    }
	
	return 1;
}