/* Entry point of code */

#include "../WeatherBalloonCommon/GlobalDefines.h"
#include "DefinesSensor.h"

#define NumberOfDataValue_Params 4
#define WATER_LEVEL_PRESSURE 102750

#include "./Drivers/uart.h"
#include "./Drivers/BMP180.h"
#include "Protocol/RadioSource.h"

#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char DeviceId;

int main(void)
{		
	//Init UART, Baudrate: 9600; bits: 8
	InitUART(9600, 8);
	
	BMP180_Init(WATER_LEVEL_PRESSURE);

	//Fetch deviceId from sensor to use in communication protocol
	DeviceId = BMP180_GetDeviceId();
		
	//Create structs and struct array for sensor data
	struct DataValue_Params TempParam;
	struct DataValue_Params PresParam;
	struct DataValue_Params AltiParam;
	struct DataValue_Params DelAltParam;
	
	TempParam.DataCommand = TEMP_CMD;
	PresParam.DataCommand = PRES_CMD;
	AltiParam.DataCommand = ALT_CMD;
	DelAltParam.DataCommand = DELALT_CMD;
	
	struct DataValue_Params DataParams[NumberOfDataValue_Params];
	
	//Primary routine
	while (1)
	{
		//Fill data structs with data from sensor
		TempParam.DataValue = BMP180_GetTemperature();
		PresParam.DataValue = BMP180_GetPressure();
		AltiParam.DataValue = BMP180_GetAltitude();
		DelAltParam.DataValue = BMP180_GetDeltaAltitude();
		
		DataParams[0] = TempParam;
		DataParams[1] = PresParam;
		DataParams[2] = AltiParam;
		DataParams[3] = DelAltParam;
		
		PerformFullTransmission(DeviceId, DataParams, (sizeof(DataParams)/sizeof(DataParams[0])));
		_delay_ms(RoutineFrequenzy);
	}
	
	return 1;
}

