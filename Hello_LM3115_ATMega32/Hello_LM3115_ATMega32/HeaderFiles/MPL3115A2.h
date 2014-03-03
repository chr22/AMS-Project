/*
 * LM3115A2.h
 *
 * Created: 25-02-2014 09:34:37
 *  Author: Casper
 */ 

#include "I2C.h"

void MPL3115_init();
unsigned char MPL3115_GetDeviceId();
unsigned long int MPL3115RegReadTemperature(unsigned char reg);
unsigned char MPL3115RegRead(unsigned char reg);
void MPL3115_RegWrite(unsigned char reg, unsigned char val);