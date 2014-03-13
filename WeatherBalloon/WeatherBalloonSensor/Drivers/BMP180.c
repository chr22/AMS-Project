#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesSensor.h"

#define SensorReadAddress 0xEF
#define SensorWriteAddress 0xEE

#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include "BMP180.h"
#include "i2c.h"


/* Private function prototypes */
//Private Init functions:
void BMP180_GetCalibrationParams();
void BMP180_GetBaseValues();
//Application Layer protocol implementation:
void BMP180_RegRead(unsigned char* RetVal, unsigned char reg, unsigned int NumOfBytes);
void BMP180_RegWrite(unsigned char reg, unsigned char val);
//Value calculation methods:
short BMP180_CalculateTrueTemperature(unsigned long ut);
long BMP180_CalculateTruePressure(unsigned long up);
double BMP180_CalculateAltitude(double Pressure);
//Start data sampling methods:
void BMP180_StartTemperatureMessurement();
void BMP180_StartPressureMessurement();



/* Global variables */
struct bmp180_calibration_params cal_param;
long BaseTemperature;
long BasePressure;
long BaseAltitude;
long SealevelPressure = 101360;		//Default value of sealevel pressure

/* Init stuff: */
void BMP180_Init(long BaseLevelPressure)
{
	SealevelPressure = BaseLevelPressure;
	
	I2C_Init();
	
	BMP180_GetCalibrationParams();
	BMP180_GetBaseValues();
}

void BMP180_GetBaseValues()
{
	//Dummy reads to fill calibration params
	BMP180_GetTemperature();
	BMP180_GetPressure();
	BMP180_GetAltitude();
	
	BaseTemperature = BMP180_GetTemperature();
	BasePressure = BMP180_GetPressure();
	BaseAltitude = BMP180_GetAltitude();
}

//Calibration values read from BMP180 EEPROM
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

/* Temperature stuff: */
void BMP180_StartTemperatureMessurement() 
{
	BMP180_RegWrite(0xF4, 0x2E);		//Starts temperature meassurement (p. 21 datasheet)
	_delay_ms(5);						//Wait for device to sample temp
}

long BMP180_GetTemperature()
{
	BMP180_StartTemperatureMessurement();
		
	unsigned char b[2];
	BMP180_RegRead(b, 0xF6, 2);
	unsigned long MSB = (unsigned long)b[0];
	unsigned long LSB = (unsigned long)b[1];
	
	unsigned long ret = (MSB<<8) + LSB;
		
	return BMP180_CalculateTrueTemperature(ret);
}

//Private
/* Taken from Bosch Sensortech ANSI C implementation of BMP180 calculations. Also described in datasheet */
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

/* Pressure stuff: */
void BMP180_StartPressureMessurement() 
{
	BMP180_RegWrite(0xF4, (0x34));
	_delay_ms(10);
}

long BMP180_GetPressure()
{
	BMP180_StartPressureMessurement();
		
	unsigned char b[2] = {' ', ' '};
	BMP180_RegRead(b, 0xF6, 2);
	long MSB = (long)b[0];
	long LSB = (long)b[1];
	
	long ret = (MSB<<8) + LSB;
	
	return BMP180_CalculateTruePressure(ret);
}

long BMP180_GetDeltaPressure()
{
	return labs(BMP180_GetPressure() - BasePressure);
}

//Private
/* Taken from Bosch Sensortech ANSI C implementation of BMP180 calculations. Also described in datasheet */
long BMP180_CalculateTruePressure(unsigned long up)
{
	//Own calc
	long p, x1, x2, x3, b3, b6;
	unsigned long b4, b7;
	
	b6 = cal_param.param_b5-4000;
	
	x1 = ((cal_param.b2 * (b6 * (b6/pow(2, 12))))/pow(2, 11));
	x2 = cal_param.ac2 * (b6/pow(2,11));
	x3 = x1 + x2;
	
	b3 = (((cal_param.ac1*4+x3)<<cal_param.oversampling_setting)+2)/4 ;
	
	x1 = cal_param.ac3 * b6 / pow(2, 13);
	x2 = (cal_param.b1 * (b6 * b6 / pow(2, 12)))/pow(2, 16);
	x3 = ((x1 + x2) + 2) / pow(2,2);
	
	b4 = cal_param.ac4 * (unsigned long)(x3 + 32768) / pow(2, 15);
	b7 = ((unsigned long)up-b3)*(50000 >> cal_param.oversampling_setting);
	if(b7 < 0x80000000)
	{
		p = (b7*2)/b4;
	}
	else
	{
		p = (b7/b4)*2;
	}
	
	x1 = (p/pow(2,8))*(p/pow(2,8));
	x1 = (x1 * 3038)/pow(2,16);
	x2 = (-7357 * p)/pow(2,16);
	p = p + (x1+x2+3791)/pow(2,4);
	
	return p;
}


/* Altitude stuff: */
double BMP180_CalculateAltitude(double Pressure) 
{
	return 44330 * (1-(pow((Pressure/SealevelPressure), (1/5.255))));
}

long BMP180_GetAltitude()
{	
	long Pressure = BMP180_GetPressure();
			
	long Altitude = BMP180_CalculateAltitude((double)Pressure);
	
	return Altitude;
}

long BMP180_GetDeltaAltitude()
{
	long temp = BMP180_GetAltitude();
	long res = labs(temp - BaseAltitude);
	
	return res;
}

//DeviceId is hardcoded in device. Usefull for protocol testing purpose
unsigned char BMP180_GetDeviceId()
{
	unsigned char RetVal[1];
	BMP180_RegRead(RetVal , 0xD0, 1);
	return RetVal[0];
}


/* Protocol Application layer: */
//Private
void BMP180_RegWrite(unsigned char reg, unsigned char val)
{
	I2C_Start();
	I2C_Write(SensorWriteAddress);
	I2C_Write(reg);
	I2C_Write(val);
	I2C_Stop();
}

//Private
void BMP180_RegRead(unsigned char* RetVal, unsigned char reg, unsigned int NumOfBytes )
{
	I2C_Start();						//S
	I2C_Write(SensorWriteAddress);		//module address write
	I2C_Write(reg);						//Register address
	I2C_RepeatedStart();

	I2C_Write(SensorReadAddress);		//Module address read
	
	//Receive:	
	for(int i = 0; i < (NumOfBytes-1); ++i)
	{
		*RetVal = I2C_Read(0);
		++RetVal;
	}
	*RetVal = I2C_Read(1);
	
	I2C_Stop();
}


