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
#include "GlobalDefines.h"
#include "uart.h"

int PerformFullTransmission(char id, char * temp, char * alt, char * pres)
{
	int err = 0;
	DataReady(id, FULL_TRANSMIT_NUM);
	err = WaitForServerReady(RADIO_TIMEOUT_MS);
	if(err < 0)
	{
		return SERVER_N_READY_ERR;
	}
	
	TemperatureSend(temp);
	AltitudeSend(alt);
	PressureSend(pres);
	
	if(!WaitForAck(RADIO_TIMEOUT_MS))
	{
				
	}
	
	return 1; 
}

int DataReady(char id, char numToTransmit)
{
	//Transmit id
	SendChar(id);
	
	//Transmit number to transmit
	SendChar(numToTransmit);
	//SendInteger(numToTransmit);
	return 1;
}

int TemperatureSend(char * temp)
{
	//SendChar(TEMP_CMD>>8);
	//SendChar(TEMP_CMD);
	
	return 1;
}

int PressureSend(char * pres)
{
	
	return 1;
}

int AltitudeSend(char * pres)
{
	
	return 1; 
}


