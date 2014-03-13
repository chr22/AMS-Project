/*
 * I2C.h
 *
 * Created: 25-02-2014 09:23:03
 *  Author: Casper
 */ 



void I2C_Init();
void I2C_Start();
void I2C_Write(unsigned char data);
unsigned char I2C_Read (unsigned char isLast);
void I2C_Stop();	
void I2C_RepeatedStart();