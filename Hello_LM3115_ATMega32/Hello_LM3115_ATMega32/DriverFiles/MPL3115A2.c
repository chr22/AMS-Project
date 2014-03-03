/*
 * MPL3115A2.c
 *
 * Created: 25-02-2014 09:38:28
 *  Author: Casper
 */ 

#define F_CPU 3686400


#include <util/delay.h>

#include "../HeaderFiles/MPL3115A2.h"
#include "../HeaderFiles/uart.h"


#define SensorReadAddress 0xEF
#define SensorWriteAddress 0xEE
#define READ_MASK 0b00000001

void MPL3115_init()
{
	i2c_init();
	//SendString("i2c init done");
	//// Example from datasheet flowchart:
	//
	//
	//MPL3115_RegWrite(SensorAddress, 0x26, 0xB8);
	//MPL3115_RegWrite(SensorAddress, 0x13, 0x07);	
	//
	//SendString("Done writing init registers");
	
	//_delay_ms(10);
	
	SendString("Hello MPL3115A2 \r\n");
	
	MPL3115_RegWrite(0xF4, 0x2E);		//Staret temperature measurement (p. 21 datasheet)
	
}

void MPL3115_RegWrite(unsigned char reg, unsigned char val)
{
	i2c_start();
	i2c_write(SensorWriteAddress);
	i2c_write(reg);
	i2c_write(val);
	i2c_stop();
}

unsigned long int MPL3115RegReadTemperature(unsigned char reg)
{
	SendString("Starting read at: \r\n");
	SendInteger((int)reg);
	unsigned char b[2] = {' ', ' '};
	
	i2c_start();						//S
	i2c_write(SensorWriteAddress);		//module address write
	i2c_write(reg);						//Register address
	i2c_stop();
	_delay_ms(5);							//Restart
	i2c_start();
	i2c_write(SensorReadAddress);		//Module address read
	SendString("Second write\r\n");
										//Receive:
	b[0] = i2c_read(1);					//Read MSB
	b[1] = i2c_read(1);					//Read LSB
	
	i2c_stop();
	
	SendString("Received: ");
	SendInteger((int)b[0]);
	SendString("Received: ");
	SendInteger((int)b[1]);
	
	
	unsigned long int ret = b[0] | (b[1]<<8);
	
	return ret;
}

unsigned char MPL3115RegRead(unsigned char reg)
{
	unsigned char b;
	
	i2c_start();						//S
	i2c_write(SensorWriteAddress);		//module address write
	i2c_write(reg);						//Register address
	i2c_stop();
	_delay_ms(5);							//Restart
	i2c_start();
	i2c_write(SensorReadAddress);		//Module address read
	SendString("Reading\r\n");
	
	//Receive:
	b = i2c_read(1);					//Read MSB
	
	return b;
}

unsigned char MPL3115_GetDeviceId()
{		
	return MPL3115RegRead(0xD0);
}