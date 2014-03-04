/*
 * MPL3115A2.c
 *
 * Created: 25-02-2014 09:38:28
 *  Author: Casper
 */ 

#define F_CPU 3686400
#include <util/delay.h>

#include "BMP180.h"
#include <stdlib.h>

#define SensorReadAddress 0xEF
#define SensorWriteAddress 0xEE


/* Private function prototypes */
void BMP180_RegRead(unsigned char* RetVal, unsigned char reg, unsigned int NumOfBytes);
void BMP180_RegWrite(unsigned char reg, unsigned char val);
short BMP180_CalculateTrueTemperature(unsigned long ut);
long BMP180_CalculateTruePressure(unsigned long up);
void BMP180_GetCalibrationParams();

/* Global variables */
struct bmp180_calibration_params cal_param;

void BMP180_GetCalibrationParams() 
{
	unsigned char temp[2];
	
	//AC1
	BMP180_RegRead(temp, 0xAA, 2);
	cal_param.ac1 = (temp[0]<<8) + temp[1];
	
	//AC2
	BMP180_RegRead(temp, 0xAC, 2);
	cal_param.ac2 = (temp[0]<<8) + temp[1];
	
	//AC3
	BMP180_RegRead(temp, 0xAE, 2);
	cal_param.ac3 = (temp[0]<<8) + temp[1];
	
	//AC4
	BMP180_RegRead(temp, 0xB0, 2);
	cal_param.ac4 = (temp[0]<<8) + temp[1];
	
	//AC5
	BMP180_RegRead(temp, 0xB2, 2);
	cal_param.ac5 = (temp[0]<<8) + temp[1];
	
	//AC6
	BMP180_RegRead(temp, 0xB4, 2);
	cal_param.ac6 = (temp[0]<<8) + temp[1];
	
	//B1
	BMP180_RegRead(temp, 0xB6, 2);
	cal_param.b1 = (temp[0]<<8) + temp[1];
	
	//B2
	BMP180_RegRead(temp, 0xB8, 2);
	cal_param.b2 = (temp[0]<<8) + temp[1];
	
	//MB
	BMP180_RegRead(temp, 0xBA, 2);
	cal_param.mb = (temp[0]<<8) + temp[1];
	
	//MC
	BMP180_RegRead(temp, 0xBC, 2);
	cal_param.mc = (temp[0]<<8) + temp[1];
	
	//MD
	BMP180_RegRead(temp, 0xBE, 2);
	cal_param.md = (temp[0]<<8) + temp[1];
	
	//Other values
	cal_param.oversampling_setting = 0;
	cal_param.param_b5 = 0;
}


void BMP180_Init()
{
	i2c_init();
	
	BMP180_GetCalibrationParams();
}

double BMP180_GetTemperature()
{
	BMP180_RegWrite(0xF4, 0x2E);		//Starts temperature meassurement (p. 21 datasheet)
	_delay_ms(4.5);						//Wait for device to sample temp
	
	unsigned char b[2];
	BMP180_RegRead(b, 0xF6, 2);
	unsigned long int ret = (b[0]<<8) + b[1];
	
	return BMP180_CalculateTrueTemperature(ret) * 0.1;
}

unsigned char BMP180_GetDeviceId()
{
	unsigned char RetVal[1];
	BMP180_RegRead(RetVal , 0xD0, 1);
	return RetVal[0];
}


//Private
void BMP180_RegWrite(unsigned char reg, unsigned char val)
{
	i2c_start();
	i2c_write(SensorWriteAddress);
	i2c_write(reg);
	i2c_write(val);
	i2c_stop();
}

//Private
void BMP180_RegRead(unsigned char* RetVal, unsigned char reg, unsigned int NumOfBytes )
{
	i2c_start();						//S
	i2c_write(SensorWriteAddress);		//module address write
	i2c_write(reg);						//Register address
	i2c_RepeatedStart();

	i2c_write(SensorReadAddress);		//Module address read
	
	//Receive:	
	for(int i = 0; i < (NumOfBytes-1); ++i)
	{
		*RetVal = i2c_read(0);
		++RetVal;
	}
	*RetVal = i2c_read(1);
	
	i2c_stop();
}


short BMP180_CalculateTrueTemperature(unsigned long ut)
{
	short temperature;
	long x1, x2;
	x1 = (((long) ut - (long) cal_param.ac6) * \
	(long) cal_param.ac5) >> 15;
	x2 = ((long) cal_param.mc << 11) / \
	(x1 + cal_param.md);
	cal_param.param_b5 = x1 + x2;
	temperature = ((cal_param.param_b5 + 8) >> 4);  /* temperature in 0.1 deg C*/
	return temperature;
}

long BMP180_CalculateTruePressure(unsigned long up)
{
	long pressure, x1, x2, x3, b3, b6;
	unsigned long b4, b7;

	b6 = cal_param.param_b5 - 4000;
	/*****calculate B3************/
	x1 = (b6*b6) >> 12;
	x1 *= cal_param.b2;
	x1 >>= 11;

	x2 = (cal_param.ac2*b6);
	x2 >>= 11;

	x3 = x1 + x2;

	b3 = (((((long)cal_param.ac1)*4 + x3) << \
	cal_param.oversampling_setting)+2) >> 2;

	/*****calculate B4************/
	x1 = (cal_param.ac3 * b6) >> 13;
	x2 = (cal_param.b1 * ((b6*b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (cal_param.ac4 * (unsigned long) (x3 + 32768)) >> 15;

	b7 = ((unsigned long)(up - b3) * (50000>>cal_param.oversampling_setting));
	if (b7 < 0x80000000)
	pressure = (b7 << 1) / b4;
	else
	pressure = (b7 / b4) << 1;

	x1 = pressure >> 8;
	x1 *= x1;
	x1 = (x1 * PARAM_MG) >> 16;
	x2 = (pressure * PARAM_MH) >> 16;
	pressure += (x1 + x2 + PARAM_MI) >> 4;/* pressure in Pa*/
	return pressure;
}