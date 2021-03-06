#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Protocol/ServerProtocol.h"

int main(void)
{
	InitServer();

	sei();
	
	while(1){}
}

ISR(USART_RXC_vect)
{
	int err = 0;
	
	err = HandleIncoming(UDR);
	
	if(err < 0)
	{}
}