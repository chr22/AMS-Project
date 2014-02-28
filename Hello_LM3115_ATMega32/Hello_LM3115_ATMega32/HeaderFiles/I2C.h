/*
 * I2C.h
 *
 * Created: 25-02-2014 09:23:03
 *  Author: Casper
 */ 



void i2c_init();
void i2c_start();
void i2c_write(unsigned char data);
unsigned char i2c_read (unsigned char isLast);
void i2c_stop();	