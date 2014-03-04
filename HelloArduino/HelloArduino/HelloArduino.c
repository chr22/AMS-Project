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
#define F_CPU 16000000
#include <util/delay.h>
#include "uart.h"
#include "RadioSource.h"


int main()
{
	//readyReg = 0x00;
	//Test values
	char testTmp[2];
	char testAlt[4];
	char testPres[4];
	char testId = 0x20;
	int err = 1;
	// Initialize the display
	InitUART(9600,8);
	
	testTmp[0] = 0x10;
	testTmp[1] = 0x10;
	
	testPres[0] = 'p';
	testPres[1] = 'r';
	testPres[2] = 'e';
	testPres[3] = 's';
	
	testAlt[0] = 'a';
	testAlt[1] = 'l';
	testAlt[2] = 't';
	testAlt[3] = 'i';
	
	
	while(1)
	{
		err = PerformFullTransmission(testId, testTmp, testAlt, testPres);
		if(err < 0)
		{
			//SendString("Failed full transmission. \n");
		}
		else
		{
			//SendString("Success!");
		}
		//_delay_ms(5000);
	}
}

ISR(TIMER0_OVF_vect)
{

}



