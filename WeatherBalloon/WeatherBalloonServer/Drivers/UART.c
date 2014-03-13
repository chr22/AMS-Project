#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesServer.h"

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "UART.h"

// Constants
#define XTAL 3686400  

volatile int readyReg;

void InitUART(unsigned long BaudRate, unsigned char DataBit)
{
unsigned int TempUBRR;

  if ((BaudRate >= 110) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
  { 
    // "Normal" clock, no multiprocessor mode (= default)
    UCSRA = 0b00100000;
    // No interrupts enabled
    // Receiver enabled
    // Transmitter enabled
    // No 9 bit operation
    UCSRB = 0b00011000;	
    // Asynchronous operation, 1 stop bit, no parity
    // Bit7 always has to be 1
    // Bit 2 and bit 1 controls the number of databits
    UCSRC = 0b10000000 | (DataBit-5)<<1;
    // Set Baud Rate according to the parameter BaudRate:
    // Select Baud Rate (first store "UBRRH--UBRRL" in local 16-bit variable,
    //                   then write the two 8-bit registers separately):
    TempUBRR = XTAL/(16*BaudRate) - 1;
    // Write upper part of UBRR
    UBRRH = TempUBRR >> 8;
    // Write lower part of UBRR
    UBRRL = TempUBRR;
	
	//Setup timer for timeout (used in ReadCharWTimeout())
	//Timer1 overflow interrupt enable
	TIMSK = 0b00000100;
	
	//Clock prescaler 64
	TCCR1B = 0b00000011;
	
	//Initialize count register to 0
	TCNT1H = 0x00;
	TCNT1L = 0x00;
  }  
  
}



/*************************************************************************
Awaits transmitter-register ready.
Then it send the character.
Parameter :
	Ch : Character for sending. 
*************************************************************************/
void SendChar(char Ch)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSRA & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR = Ch;
}

//Blocks until char has been received or timeout(s) has occured
int ReadCharWTimeout(char * retVal, int timeOutMs)
{
	readyReg = 0;
	int err = 1;
	
	//disable RX complete interrupt interrupt
	UCSRB &= 0b01111111;	
	sei();
		
	// Wait for new character received or Timeout overflow
	while(((UCSRA & (1<<7)) == 0) && (readyReg < 8))
	{ }
	
	//While loop was broken by overflow timer, so we got no response from server.
	if(readyReg >= 8)
	{
		err = TIMEOUT_ERR;
	}
	else
	{
		*retVal = UDR;
	}
	
	cli();
	//enable RX complete interrupt interrupt
	UCSRB |= (1 << RXCIE);	

	return err;
}

ISR(TIMER1_OVF_vect)
{
	++readyReg;
}

