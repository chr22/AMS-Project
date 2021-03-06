/*
 * I2C.c
 *
 * Created: 25-02-2014 09:22:46
 *  Author: Casper
 */ 
#include "../Drivers/I2C.h"
#include "../Util/GlobalDefines.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void i2c_init()
{
	sei();
	// TWI prescaler = 1 (same as default)
	TWSR = 0;
	// LM75 clock has be to be lower than 400 kHz (according to LM75 data sheet)
	// We choose 2-wire clock ~ 50 kHz
	// The TWBR must be at least 10 in master mode (Mega32 data book)
	// SCL frequency = 3.6864 MHz / (16 + 2*TWBR*1), when prescaler = 1
	TWBR = 152;	//Atmega32u4 = 40 kHz, Atmega32 = 11.5 kHz
}

void i2c_start()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
	{
		//Todo: fanget her
	}
	//SendString("Done i2c start");
}

void i2c_write(unsigned char data)
{
	
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
	{}
	//SendString("Done writing");
}

unsigned char i2c_read (unsigned char isLast)
{
	if (isLast == 0) //If we want to read more than 1 byte
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	else             //If we want to read only one byte
	TWCR = (1<<TWINT) | (1<<TWEN);
	//SendString("Before read loop\r\n");
	while ((TWCR & (1<<TWINT)) == 0)
	{
		//SendString("read loop \r\n");
	}
	//SendString("Done reading\r\n");
	return TWDR;
}

void i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void i2c_RepeatedStart()
{
	i2c_stop();
	_delay_ms(3);							//Restart
	i2c_start();
}