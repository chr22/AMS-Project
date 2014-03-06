/*
 * LM3115A2.h
 *
 * Created: 25-02-2014 09:34:37
 *  Author: Casper
 */ 

#define PARAM_MG      3038        /*calibration parameter */
#define PARAM_MH     -7357        /*calibration parameter */
#define PARAM_MI      3791        /*calibration parameter */

#include "I2C.h"

void BMP180_Init();
unsigned char BMP180_GetDeviceId();
double BMP180_GetTemperature();
long BMP180_GetPressure();
double BMP180_GetAltitude();

//unsigned char BMP180_RegRead(unsigned char[] RetVal, unsigned char reg, unsigned int NumOfBytes);
//void BMP180_RegWrite(unsigned char reg, unsigned char val);


/* this structure holds all device specific calibration parameters */
struct bmp180_calibration_params{
	short ac1;
	short ac2;
	short ac3;
	unsigned short ac4;
	unsigned short ac5;
	unsigned short ac6;
	short b1;
	short b2;
	short mb;
	short mc;
	short md;
	long param_b5;
	short oversampling_setting;
};