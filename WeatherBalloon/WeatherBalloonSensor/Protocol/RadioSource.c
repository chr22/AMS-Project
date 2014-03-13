#include "ProtocolLayer.h"
#include "RadioSource.h"
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesSensor.h"
#include "../Drivers/UART.h"
#include <math.h>

int PerformFullTransmission( char id, struct DataValue_Params* data_params, int params_count )
{
	int retryCount = 0;
	int err = 0;
	int i = 0;
	
	//Transmit SensorReady and wait for server to echo the SensorID back 
	err = -1;
	while(err < 0 && retryCount < 3)
	{
		DataReady(id, params_count);
		err = WaitForServerReady(RADIO_TIMEOUT_MS, id);
		if(!err)
		{
			++retryCount;
		}
	}
	if (retryCount >= 3)
	{
		return SERVER_N_READY_ERR;
	}
	
	//Transmit Data and wait for 
	retryCount = 0;
	err = -1;
	while(err < 0 && retryCount < 3)
	{
		for(i = 0; i < params_count; i++)
		{
			TransmitMeasurement(data_params[i].DataCommand, data_params[i].DataValue, id);
		}
						
		err = WaitForAck(RADIO_TIMEOUT_MS, id);
		
		if(err < 0)
		{
			++retryCount;
		}
	}
	
	if (retryCount >= 3)
	{
		return -1;
	}
	
	return 1; 
}


