/*
 * ServerSideRadioProject.c
 *
 * Created: 02-03-2014 17:30:47
 *  Author: Nikolaj
 */ 


#include <avr/io.h>
#define F_CPU 3686400
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Drivers/uart.h"
#include "Protocol/ServerProtocol.h"
#include "Drivers/lcd162.h"



int main(void) 
{
	LCDInit();
	InitUART(9600, 8);
	UCSRB |= (1 << RXCIE); 
	
	LCDDispString("Hello world!");
	LCDClear();
	SendString("Program begun.");
	sei();
	
    while(1)
    {
        
    }
}

ISR(USART_RXC_vect)
{
	HandleIncoming(UDR);
}
