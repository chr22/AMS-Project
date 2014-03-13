#include <math.h>
#include "ProtocolLayer.h"
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesSensor.h"
#include "../Drivers/UART.h"

//Wait for server to send ServerReady command. (Echo of sent ID)
int WaitForServerReady(int timeOutMs, unsigned char id)
{
	int err = -1;
	char * retVal = 0x00;
	int retryCount = 0;
	
	//Retry 3 times
	while((err < 0) && (retryCount < 3))
	{
		err = ReadCharWTimeout(retVal, timeOutMs);
		++retryCount;	
	}
	
	if(err < 0)
	{
		return err;
	}	
	
	if(*retVal != id)
	{
		return WRONG_ID_ERR;
	}

	return 1;
}

//Calculate number of bytes needed to send transmission
int CalculateTransmissionLength(long measureVal ) 
{
	int bitVal = log(measureVal)/log(2) + 1;
	int byteNum = bitVal/8 + 1;
	return byteNum;
}

//Converts long to hex values and add to byte array
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
	int transmissionLength = CalculateTransmissionLength(measureVal);
	char measureInBytes[transmissionLength];
	err = ConvertIntToCharArray(measureVal, transmissionLength, measureInBytes);	
	
	//Send Type command
	SendChar(measureType);
	
	//Send length field
	SendChar((char)transmissionLength);
	
	//Foreach value in byteArray, send that byte
	for(i = 0; i < transmissionLength; ++i)
	{
		SendChar(measureInBytes[i]);	
	}
	
	if(err < 0)
	{
		return err;
	}
	
	return 1;
}

//Wait for received Acknowledge command from sensor, following a transmission of data
int WaitForAck( int timeOutMs, unsigned char id )
{
	char * retVal = 0x00;
	int err = 0;
	
	//Wait for ACK command byte
	err = ReadCharWTimeout(retVal, timeOutMs);
	if (err < 0)
	{
		return err;
	}
	if(*retVal != ACK_CMD)
	{
		return UNEXPECTED_CMD_ERR;
	}
	
	//Wait for ID byte
	err = ReadCharWTimeout(retVal, timeOutMs);
	if(err < 0)
	{
		return err;
	}
	if(*retVal != id)
	{
		return WRONG_ID_ERR;
	}
	
	return err;
}

int DataReady( char id, int numToTransmit )
{
	//Transmit ReadyCommand
	SendChar(RDY_CMD);
	
	//Transmit id
	SendChar(id);
	
	//Transmit number to transmit
	SendChar((char)numToTransmit);
	return 1;
}