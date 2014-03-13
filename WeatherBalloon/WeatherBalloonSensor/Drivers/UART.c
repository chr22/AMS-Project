#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesSensor.h"
#include "UART.h"

#define XTAL 16000000

volatile int readyReg;  

//Setup UART
//Setup timer1 for overflow interrupts (used in ReadCharWTimeout)
void InitUART(unsigned long BaudRate, unsigned char DataBit)
{
unsigned int TempUBRR;

  if ((BaudRate >= 110) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
  { 
    // "Normal" clock, no multiprocessor mode (= default)
    UCSR1A = 0b00100000;
    // No interrupts enabled
    // Receiver enabled
    // Transmitter enabled
    // No 9 bit operation
    UCSR1B = 0b00011000;	
    // Asynchronous operation, 1 stop bit, no parity
    // Bit7 always has to be 1
    // Bit 2 and bit 1 controls the number of databits
    UCSR1C = 0b10000000 | (DataBit-5)<<1;
    // Set Baud Rate according to the parameter BaudRate:
    // Select Baud Rate (first store "UBRRH--UBRRL" in local 16-bit variable,
    //                   then write the two 8-bit registers separately):
    TempUBRR = XTAL/(16*BaudRate) - 1;
    // Write upper part of UBRR
    UBRR1H = TempUBRR >> 8;
    // Write lower part of UBRR
    UBRR1L = TempUBRR;
  }  
  

  //Timer1 overflow interrupt enable
  TIMSK1 = 0b00000001;
  
  //Clock prescaler 1024
  TCCR1B = 0b00000101;
  
  //Timer counter registers initialized to 0
  TCNT1H = 0x00;
  TCNT1L = 0x00;
  
  readyReg = 0;
}

//Blocks until char has been received or timeout(s) has occured
int ReadCharWTimeout(char * retVal, int timeOutMs)
{
	readyReg = 0;
	int err = 1;
	sei();
	
	// Wait for new character received or (2) timer1 overflows
	while(((UCSR1A & (1<<7)) == 0) && (readyReg < 2))
	{ }	
	
	//While loop was broken by overflow timer, so we got no response from server.
	if(readyReg >= 3)
	{
		err = TIMEOUT_ERR;
	}
	else
	{
		*retVal = UDR1;	
	}
	cli();
	return err;
}

ISR(TIMER1_OVF_vect)
{
	++readyReg;
}


/*************************************************************************
Awaits transmitter-register ready.
Then it send the character.
Parameter :
	Ch : Character for sending. 
*************************************************************************/
void SendChar(char Ch)
{
  // Wait for transmitter register empty
  while ( (UCSR1A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR1 = Ch;
}