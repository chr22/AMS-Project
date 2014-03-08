/*
 * RadioSource.c
 *
 * Created: 25-02-2014 10:15:39
 *  Author: Nikolaj
	Desciption:
		Implementation of layer between UART and Business logic
 */ 

#include "ProtocolLayer.h"
#include "RadioSource.h"
#include "../Util/GlobalDefines.h"
#include "../Drivers/uart.h"
#include <math.h>

int PerformFullTransmission( char id, struct DataValue_Params* data_params, int params_count)
{
	int retryCount = 0;
	int err = 0;
	
	//Transmit SensorReady and wait for server to echo the SensorID back 
	err = -1;
	while(err < 0 && retryCount < 3)
	{
		DataReady(id, 4);
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
		TransmitMeasurement(TEMP_CMD, DataValue_Params, id);
		TransmitMeasurement(ALT_CMD, data_params, id);
		TransmitMeasurement(DELALT_CMD, DeltaAlt, id);
		TransmitMeasurement(PRES_CMD, pres, id);
						
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

int DataReady(char id, char numToTransmit)
{
	//Transmit ReadyCommand
	SendChar(RDY_CMD);
	
	//Transmit id
	SendChar(id);
	
	//Transmit number to transmit
	SendChar(numToTransmit);
	//SendInteger(numToTransmit);
	return 1;
}


