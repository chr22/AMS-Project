/*
 * RadioServerTest.c
 *
 * Created: 05-03-2014 20:31:13
 *  Author: Nikolaj
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd162.h"
#include "ServerProtocol.h"
#include "uart.h"
#include "GlobalDefines.h"

int main(void)
{
	char k = 'b';
	InitUART(9600, 8);
	LCDInit();
	//Enable receive-byte interrupt
	UCSRB |= (1 << RXCIE);
	//SendString("Hullo");
	SendChar(0x50);
	SendChar(0x50);
	//SendChar(0x50);
	
	LCDDispString("Main");
	sei();
	
    while(1)
    {
		//k = ReadChar();
		//LCDClear();
		//LCDDispChar(k);
        //TODO:: Please write your application code 
    }
}

ISR(USART_RXC_vect)
{
	//LCDDispChar('a');
	HandleIncoming(UDR);
}