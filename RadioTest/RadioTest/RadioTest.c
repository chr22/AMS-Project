/*
 * RadioTest.c
 *
 * Created: 04-03-2014 21:32:10
 *  Author: Nikolaj
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "ProtocolLayer.h"
#include "RadioSource.h"

int main(void)
{
	int err = 0;
	InitUART(9600, 8);
	//SendString("New Hello.");
	SendChar(0x10);
	SendChar(0x10);
	SendChar(0x10);
	err = PerformFullTransmission(0x20, 80000, 3003, 3276);
	
	if(!(err <0))
	{
		SendString("DONE");
	}
	//return 1;
    while(1)
    {
		//SendString("Hello!");
        //TODO:: Please write your application code 
    }
	return 1;
}

