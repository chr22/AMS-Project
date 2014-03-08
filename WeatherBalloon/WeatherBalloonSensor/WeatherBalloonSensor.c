/*
* WeatherBalloonSensor.c
*
* Created: 04-03-2014 11:21:49
*  Author: Nikolaj
*/

#include "./Util/GlobalDefines.h"
#include "./Drivers/uart.h"


#include "./Drivers/BMP180.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Protocol/RadioSource.h"

unsigned char DeviceId;

int main(void)
{		
	InitUART(9600, 8);
	_delay_ms(20);
	
	BMP180_Init();

	DeviceId = BMP180_GetDeviceId();
		
	struct DataValue_Params DataParams[4];
	
	struct DataValue_Params TempParam;
	struct DataValue_Params PresParam;
	struct DataValue_Params AltiParam;
	struct DataValue_Params DelAltParam;
	
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
		
		PerformFullTransmission(DeviceId, DataParams);
		_delay_ms(5000);
	}
	
	return 1;
}

