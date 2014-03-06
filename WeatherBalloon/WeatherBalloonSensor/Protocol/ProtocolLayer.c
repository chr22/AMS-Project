/*
 * ProtocolLayer.c
 *
 * Created: 28-02-2014 10:36:40
 *  Author: Nikolaj
 */ 

#include <math.h>
#include "ProtocolLayer.h"
#include "../Util/GlobalDefines.h"
#include "../Drivers/uart.h"

int WaitForServerReady(int timeOutMs)
{
	int err = -1;
	char * retVal = 0x00;
	int retryCount = 0;
	
	//SendString("Waiting for server ready signal. \n");
	while((err < 0) && (retryCount < 3))
	{
		err = ReadCharWTimeout(retVal, timeOutMs);
		++retryCount;	
	}
	
	if(err < 0)
	{
		return err;
	}	
	
	if(*retVal != SOURCE_ID)
	{
		//SendString("Wrong ID error. \n");
		return WRONG_ID_ERR;
	}

	return 1;
}

int CalculateTransmissionLength(long measureVal ) 
{
	int bitVal = log(measureVal)/log(2) + 1;
	int byteNum = bitVal/8 + 1;
	return byteNum;
}


int ConvertIntToCharArray(long measureVal, int transmissionLength, char * buf)
{
	int i = 0;
	for (i = 0; i < transmissionLength; ++i)
	{
		*(buf + i) = (measureVal >> ((transmissionLength-1-i) * 8)) & 0xFF; 
	}
	
	/*	
	*(buf + 0) = (measureVal >> (transmissionLength-1-0 * 8)) & 0xFF; 
	*(buf + 1) = (measureVal >> (transmissionLength-1-1 * 8)) & 0xFF; 
	*(buf + 2) = (measureVal >> (transmissionLength-1-2 * 8)) & 0xFF; 
	*/
	
	return 1;
}

int TransmitMeasurement(char measureType, long measureVal, char id)
{
	int err = -1;
	int i = 0;
	//int retryCount = 0;
	int transmissionLength = CalculateTransmissionLength(measureVal);
	char measureInBytes[transmissionLength];
	//char measureInBytes[4];
	err = ConvertIntToCharArray(measureVal, transmissionLength, measureInBytes);	
	
	SendChar(measureType);
	//SendChar(id);
	SendChar((char)transmissionLength);
	for(i = 0; i < transmissionLength; ++i)
	{
		SendChar(measureInBytes[i]);	
	}
	
	if(err < 0)
	{
		return err;
	}
	
	//SendChar(measureType);
	//SendChar(transmissionLength);
	
	//free(measure);
	return 1;
	/*
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
	*/
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
		//SendString("Wrong ID string (WaitForAck). \n");
		return WRONG_ID_ERR;
	}
	
	return 1;
}

