/*
 * MPL3115A2.c
 *
 * Created: 25-02-2014 09:38:28
 *  Author: Casper
 */ 

#include "../HeaderFiles/MPL3115A2.h"
#include "../HeaderFiles/uart.h"

#define SensorReadAddress 0xC0
#define SensorWriteAddress 0xC1
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
	SendString("Hello MPL3115A2 \r\n");
}

void MPL3115_RegWrite(unsigned char address, unsigned char reg, unsigned char val)
{
	i2c_start();
	i2c_write(address);
	i2c_write(reg);
	i2c_write(val);
	i2c_stop();
}

unsigned char MPL3115RegRead(unsigned char reg)
{
	unsigned char b;
	i2c_start();
	i2c_write(SensorWriteAddress);
	i2c_write(reg);
	i2c_start();
	i2c_write(SensorReadAddress);
	b = i2c_read(0);
	b = i2c_read(1);
	i2c_stop();
	
	return b;
}

unsigned char MPL3115_GetDeviceId()
{
	SendString("Getting device id");
	char ret = MPL3115RegRead(0x0C);
	
	return ret;
}