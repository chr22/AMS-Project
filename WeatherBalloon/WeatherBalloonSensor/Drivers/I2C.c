#include "../Drivers/I2C.h"
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesSensor.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void I2C_Init()
{
	sei();
	// TWI prescaler = 1 (same as default)
	TWSR = 0;
	// SCL frequency = 3.6864 MHz / (16 + 2*TWBR*1), when prescaler = 1
	TWBR = 152;	//Atmega32u4 = 40 kHz, Atmega32 = 11.5 kHz
}

void I2C_Start()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
	{}
}

void I2C_Write( unsigned char data )
{
	
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0)
	{}
}

unsigned char I2C_Read( unsigned char isLast )
{
	if (isLast == 0) //If we want to read more than 1 byte
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	else             //If we want to read only one byte
	TWCR = (1<<TWINT) | (1<<TWEN);

	while ((TWCR & (1<<TWINT)) == 0)
	{}
	return TWDR;
}

void I2C_Stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

//A Repeated start according to I2C standard
void I2C_RepeatedStart()
{
	I2C_Stop();
	_delay_ms(3);
	I2C_Start();
}