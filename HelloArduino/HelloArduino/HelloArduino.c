/************************************************
*  AMS: LAB5                                    *
*  LM75 and the Mega32 2-wire Interface         *
*                                               *
*  STK500 setup:                                *
*    Header "RS232 spare" connected to RXD/TXD: *
*      RXD = PORTD, bit0                        *
*      TXD = PORTD, bit1                        *
*    I2C data bus (LM75 slaves):                *
*      SCL connected to PORTC, bit0             *
*      SDA connected to PORTC, bit1             *
*    Two LM75 slaves powered from STK500:       *
*      Address no.1 = 0.                        *
*      Address no.2 = 7.                        *
*                                               *
*   Henning Hargaard, February 7, 2014          *
*************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
//#define F_CPU 16000000
#include <util/delay.h>
#include "uart.h"
#include "RadioSource.h"


int main()
{
	//readyReg = 0x00;
	//Test values
	char * testTmp = 0x00;
	char * testAlt = 0x00;
	char * testPres = 0x00;
	//char testId = 0xAA;
	
	*testTmp = 'A';
	*testAlt = 'B';
	*testPres = 'C';
	
	// Initialize the display
	InitUART(9600,8);
	
	
	while (1)
	{
		//PerformFullTransmission(testId, testTmp, testAlt, testPres);
		ReadCharWTimeout(0, 1000);
		//SendChar(0x15);
		//_delay_ms(500);
	}
}

ISR(TIMER0_OVF_vect)
{
	//SendChar(0x10);
	//cli();
	//SendChar(0x05);
	//sei();
}



