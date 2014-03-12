/*
* WeatherBalloonSensor.c
*
* Created: 04-03-2014 11:21:49
*  Author: Nikolaj
*/

#include "../WeatherBalloonCommon/GlobalDefines.h"
#include "DefinesSensor.h"
#include "./Drivers/uart.h"


#include "./Drivers/BMP180.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Protocol/RadioSource.h"

unsigned char DeviceId;

#define NumberOfDataValue_Params 4

int main(void)
{		
	InitUART(9600, 8);
	
	BMP180_Init(102600);

	DeviceId = BMP180_GetDeviceId();
		
	struct DataValue_Params TempParam;
	struct DataValue_Params PresParam;
	struct DataValue_Params AltiParam;
	struct DataValue_Params DelAltParam;
	
	struct DataValue_Params DataParams[NumberOfDataValue_Params];
	
	TempParam.DataCommand = TEMP_CMD;
	PresParam.DataCommand = PRES_CMD;
	AltiParam.DataCommand = ALT_CMD;
	DelAltParam.DataCommand = DELALT_CMD;
	
	while (1)
	{
		TempParam.DataValue = BMP180_GetTemperature();
		PresParam.DataValue = BMP180_GetPressure();
		AltiParam.DataValue = BMP180_GetAltitude();
		DelAltParam.DataValue = BMP180_GetDeltaAltitude();
		
		DataParams[0] = TempParam;
		DataParams[1] = PresParam;
		DataParams[2] = AltiParam;
		DataParams[3] = DelAltParam;
		
		//(sizeof(DataParams)/sizeof(DataParams[0]))
		PerformFullTransmission(DeviceId, DataParams, NumberOfDataValue_Params);
		_delay_ms(2000);
	}
	
	return 1;
}

