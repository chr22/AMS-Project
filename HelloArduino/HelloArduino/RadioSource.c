/*
 * RadioSource.c
 *
 * Created: 25-02-2014 10:15:39
 *  Author: Nikolaj
	Desciption:
		Implementation of layer between UART and Business logic
 */ 


#include "RadioSource.h"
#include "GlobalDefines.h"
#include "uart.h"

int PerformFullTransmission(char id, char * temp, char * alt, char * pres)
{
	DataReady(id, FULL_TRANSMIT_NUM);
	if(!WaitForServerReady(RADIO_TIMEOUT_MS))
	{
		//Server did NOT send ready
		//Return with error value
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

int DataReady(char id, int numToTransmit)
{
	//Transmit id
	SendChar(id);
	
	//Transmit number to transmit
	SendChar(FULL_TRANSMIT_NUM);
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

int WaitForServerReady(int timeOutMs)
{
	//Setup timer interrupt
	//
	
	return 1;
}

int WaitForAck(int timeOutMs)
{
	
	return 1;
}