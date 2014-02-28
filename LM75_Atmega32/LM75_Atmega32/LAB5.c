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
#define F_CPU 3686400
#include <util/delay.h>
#include "uart.h"

#define LM75_BASE_ADDRESS 0b01001000
#define READ_MASK         0b00000001

void i2c_init()
{
  // TWI prescaler = 1 (same as default)
  TWSR = 0;
  // LM75 clock has be to be lower than 400 kHz (according to LM75 data sheet)
  // We choose 2-wire clock ~ 50 kHz
  // The TWBR must be at least 10 in master mode (Mega32 data book)
  // SCL frequency = 3.6864 MHz / (16 + 2*TWBR*1), when prescaler = 1
  TWBR = 29;
}

void i2c_start()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
{}
}

void i2c_write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
{}
}

unsigned char i2c_read (unsigned char isLast)
{
	if (isLast == 0) //If we want to read more than 1 byte
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	else             //If we want to read only one byte
	TWCR = (1<<TWINT) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
{}
	return TWDR;
}

void i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

// The (positive) temperatures is send to the terminal
// Format: "T1 = xx,x C  T2 = xx,x C"
// Temp1 and Temp2 = 1/2 of centigrades
void PrintTemperatures(int Temp1)
{
	SendString("T1 = ");

	SendInteger(Temp1/2);
	SendChar(',');
	if (Temp1 & 1)
	SendChar('5');
	else
	SendChar('0');

	SendString(" C  T2 = ");
}

// Reads the temperature register from specified sensor
// SensorAddress is between 0 and 7
int LM75_temperature(unsigned char SensorAddress)
{
int temperature;

  i2c_start();
  i2c_write(((LM75_BASE_ADDRESS + SensorAddress)<<1) | READ_MASK);
  // Read temperature high byte and ACK
  temperature = i2c_read(0);
  // Shift data to high byte
  temperature = temperature << 8 ;
  // Read temperature low byte and NACK
  // Merge to temperature variable
  temperature = temperature + i2c_read(1);
 i2c_stop();
 // Return right adjusted data (see LM75 data sheet)
  return (temperature>>7);
}

int main()
{
	InitUART(9600,8);
		
	SendString("Hej");
	
	// Initialize the 2 wire interface
	i2c_init();
	// Initialize the display
	while (1)
	{
		// Read and display the temperature of sensor #0 and #7
		PrintTemperatures(LM75_temperature(0));
		// Avoid self heating
		_delay_ms(500);
		
		SendString("Hej verden igen");
	}
}