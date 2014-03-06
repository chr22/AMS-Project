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

int PerformFullTransmission(char id, long temp, long alt, long pres)
{
	int retryCount = 0;
	int err = 0;
	//DataReady(id, FULL_TRANSMIT_NUM);
	DataReady(id, 1);
	err = WaitForServerReady(RADIO_TIMEOUT_MS);
	if(err < 0)
	{
		return SERVER_N_READY_ERR;
	}
	
	
	//SendString("Ready to transmit temperatures.\n");
	TransmitMeasurement(TEMP_CMD, temp, id);
	//TransmitMeasurement(ALT_CMD, alt, id);
	//TransmitMeasurement(PRES_CMD, pres);

	
	err = -1;
	//SendString("Wait for Ack. \n");
	while(err < 0 && retryCount < 3)
	{
		++retryCount;
		err = WaitForAck(RADIO_TIMEOUT_MS);
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

int TemperatureSend(char temp[])
{
	//SendString("Temperature: ");
	//Transmit temperature command
	SendChar(TEMP_CMD);
	
	//Transmit each byte of the temperature (16 bit, so two chars)
	SendChar(temp[0]);
	SendChar(temp[1]);
	
	return 1;
}

int PressureSend(char pres[])
{
	//SendString("Pressure: ");
	SendChar(PRES_CMD);
	
	SendChar(pres[0]);
	SendChar(pres[1]);
	SendChar(pres[2]);
	SendChar(pres[3]);
	
	return 1;
}

int AltitudeSend(char alt[])
{
	//SendString("Altitude: ");
	SendChar(ALT_CMD);
	SendChar(alt[0]);
	SendChar(alt[1]);
	SendChar(alt[2]);
	SendChar(alt[3]);
	
	return 1; 
}


