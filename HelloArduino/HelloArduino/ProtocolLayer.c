/*
 * ProtocolLayer.c
 *
 * Created: 28-02-2014 10:36:40
 *  Author: Nikolaj
 */ 
#include "ProtocolLayer.h"
#include "GlobalDefines.h"
#include "uart.h"

int WaitForServerReady(int timeOutMs)
{
	int err = -1;
	char * retVal = 0x00;
	int retryCount = 0;
	
	//SendString("Waiting for server ready signal. \n");
	while((err < 0) && (retryCount < 3))
	{
		//SendString("Waiting for ready: ");
		//SendInteger(retryCount);
		//SendString("\n");
		
		err = ReadCharWTimeout(retVal, timeOutMs);
		++retryCount;	
	}
	if(err < 0)
	{
		return err;
	}	
	
	if(*retVal != SOURCE_ID)
	{
		SendString("Wrong ID error. \n");
		return WRONG_ID_ERR;
	}

	return 1;
}

int TransmitMeasurement(char measureType, int measureVal)
{
	int err = -1;
	int retryCount = 0;
	SendChar(measureType);
	SendChar((char)measureVal);
	//SendInteger(measureVal);
	
	while(err < 0 && retryCount < 3)
	{
		err = WaitForAck(5000);
		++retryCount;
	}
	if (err < 0)
	{
		return err;
	}
		
	return 1;	
}

int WaitForAck(int timeOutMs)
{
	char * retVal = 0x00;
	int err = 0;
	
	//SendString("Send ACK (0x06): \n");
	err = ReadCharWTimeout(retVal, timeOutMs);
	if (err < 0)
	{
		return err;
	}
	if(*retVal != ACK_CMD)
	{
		//SendString("Wrong CMD string (WaitForAck). \n");
		return UNEXPECTED_CMD_ERR;
	}
	
	//SendString("Send ID (0x20): \n");
	err = ReadCharWTimeout(retVal, timeOutMs);
	if(err < 0)
	{
		return err;
	}
	if(*retVal != SOURCE_ID)
	{
		SendString("Wrong ID string (WaitForAck). \n");
		return WRONG_ID_ERR;
	}
	
	return 1;
}

