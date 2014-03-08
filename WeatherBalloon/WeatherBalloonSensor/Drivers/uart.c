/**************************************************
* "uart.c":                                       *
* Implementation file for the Mega32 UART driver. *
*  STK500 setup:                                  *
*  Header "RS232 spare" connected to RXD/TXD:     *
*  RXD = PORTD, bit0                              *
*  TXD = PORTD, bit1                              *
*                                                 *
* Henning Hargaard, 1/11 2011                     *
***************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesSensor.h"
#include "uart.h"

// Constants
//#define XTAL 3686400  
#define XTAL 16000000

volatile int readyReg;  

/*************************************************************************
USART initialization.
    Asynchronous mode.
	RX and TX enabled.
	No interrupts enabled.
	Number of Stop Bits = 1.
	No Parity.
	Baud rate = Parameter.
	Data bits = Parameter.
Parameters:
	BaudRate: Wanted Baud Rate.
	Databits: Wanted number of Data Bits.
*************************************************************************/
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
  
  TIMSK1 = 0b00000001;
  TCCR1B = 0b00000101;
  TCNT1H = 0x00;
  TCNT1L = 0x00;
  
  readyReg = 0;
  //Setup of timer0 for interrupts
  //TIMSK0 = (1<<TOIE0);
  //TCNT0	= 0x00;
  //TCCR0A = (1<<CS01) | (1<<CS00);
  //TCCR0B = (1<<CS01) | (1<<CS00);
  //sei();
}


/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return UCSR1A & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
  // Wait for new character received
  while ( (UCSR1A & (1<<7)) == 0 )
  {}                        
  // Then return it
  return UDR1;
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
  while ( (UCSR1A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR1 = Ch;
}

/*************************************************************************
Sends 0-terminated string.
Parameter:
   String: Pointer to the string. 
*************************************************************************/
void SendString(char* String)
{
  // Repeat untill zero-termination
  while (*String != 0)
  {
    // Send the character pointed to by "String"
    SendChar(*String);
    // Advance the pointer one step
    String++;
  }
}

/*************************************************************************
Converts the integer "Number" to an ASCII string - and then sends this
string using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
      Number: The integer to be converted and send. 
*************************************************************************/
void SendInteger(int Number)
{
char array[7];
  // Convert the integer to an ASCII string (array), radix = 10 
  itoa(Number, array, 10);
  // - then send the string
  SendString(array);
}

/**************************************************/

int ReadCharWTimeout(char * retVal, int timeOutMs)
{
	readyReg = 0;
	int err = 1;
	sei();
	// Wait for new character received or Timeout overflow
	while(((UCSR1A & (1<<7)) == 0) && (readyReg < 3))
	{ }	
	
	//While loop was broken by overflow timer, so we got no response from server.
	if(readyReg >= 3)
	{
		SendChar(0xFF);
		SendChar(0xFF);
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

