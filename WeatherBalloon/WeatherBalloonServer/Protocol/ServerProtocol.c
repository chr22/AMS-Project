/*
 * ServerProtocol.c
 *
 * Created: 02-03-2014 17:48:09
 *  Author: Nikolaj
 */ 
#include <avr/interrupt.h>
#include "../Protocol/ServerProtocol.h"
#include "../Drivers/uart.h"
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "../DefinesServer.h"

#include "../Wrappers/DisplaySensorData.h"
#include "../Wrappers/DisplayWrapper.h"


int HandleIncoming(char cmd)
{
	int err = 0;
	
	if(cmd == RDY_CMD)
	{
		err = HandleReadyCommand();		
	}
	return err;
}

int HandleReadyCommand()
{
	char sensorID, numToRead;
	//char firstCommand = 0x00;
	
	int err = 0;
	//cli();
	//SendChar(0x80);
	err = ReadCharWTimeout(&sensorID, RADIO_TIMEOUT_MS);
	if (err < 0)
	{
		return HANDLE_TRANMISSION_ERR;
	}
	
	err = ReadCharWTimeout(&numToRead, RADIO_TIMEOUT_MS);
	if (err < 0)
	{
		return HANDLE_TRANMISSION_ERR;
	}
		
	//Send server ready
	SendChar(sensorID);
	
	err = HandleTransmission(sensorID, (int)numToRead);
	
	if (err < 0)
	{
		return HANDLE_TRANMISSION_ERR;
	}
	
	sei();

	return 1;
}

int HandleTransmission(char sensorID, int numToRead)
{
	int i = 0;
	int err = 0;
	char cmd;
	
	MeasurementStruct tmpMeasureStruct;
	//MeasurementStruct sensorArray[numToRead];
	
	//ClearScreenSensorData();
	
	while(i < numToRead)
	{
		err = ReadCharWTimeout(&cmd, RADIO_TIMEOUT_MS);
		
		if (err < 0)
		{			
			return HANDLE_TRANMISSION_ERR;
		}
				
		err = HandleValueCommand(cmd, sensorID, &tmpMeasureStruct, i);
		if (err < 0)
		{
			return HANDLE_TRANMISSION_ERR;
		}
		++i;		
	}
	
	SendAck(sensorID);
		
	err = SendToDisplay(&tmpMeasureStruct, numToRead);
			
	return err;
}

int SendToDisplay(MeasurementStruct * sensorStruct, int numberOfValues)
{
	int i = 0;

	for (i = 0; i < numberOfValues; i++)
	{		
		switch(sensorStruct->sensorValues[i].cmd)
		{
			case TEMP_CMD:
				SetLineNum(TEMP_LINE);
				WriteTempFloat(sensorStruct->sensorValues[i].sensorValue);
				break;
			case ALT_CMD:
				SetLineNum(ALT_LINE);
				WriteAltitudeFloat(sensorStruct->sensorValues[i].sensorValue);
				break;
			case PRES_CMD:
				SetLineNum(PRES_LINE);
				WritePressureFloat(sensorStruct->sensorValues[i].sensorValue);
				break;
			case DELALT_CMD:
				SetLineNum(DELTAALT_LINE);
				WriteDelAltitudeFloat(sensorStruct->sensorValues[i].sensorValue);
				break;			
			default:
				WriteToDisplay("1234");
				NewLine();
				break;
		}
	}		
	
	return 1;
}

void SendAck(char sensorID)
{
	SendChar(ACK_CMD);
	SendChar(sensorID);
}

int HandleValueCommand(char cmd, char sensorID, MeasurementStruct * returnStruct, int arrayPos)
{
	int bytesInTransmission = 0;
	char tmpBytesInTransmission = 0;
	int i = 0;
	int err = 0;
	long tmpSensorvalue = 0;
	
	//First byte after command is length field
	err = ReadCharWTimeout(&tmpBytesInTransmission, RADIO_TIMEOUT_MS);
	if (err < 0)
	{
		return HANDLE_TRANMISSION_ERR;
	}
	bytesInTransmission = (int)tmpBytesInTransmission;
	
	//(*returnStruct).cmd = cmd;
	//(*returnStruct).arrayLength = bytesInTransmission;
	
	char sensorValue[bytesInTransmission];
	
	for (i = 0; i < bytesInTransmission; ++i )
	{
		err = ReadCharWTimeout(&sensorValue[i], RADIO_TIMEOUT_MS);
		
		if (err < 0)
		{
			//SendString("under 0");
			return HANDLE_TRANMISSION_ERR;
		}
	}
	
	tmpSensorvalue = CalculateIntFromBytes(sensorValue, bytesInTransmission);
	
	if (arrayPos <= MAX_NUM_OF_SENSORVALUES)
	{
		returnStruct->sensorValues[arrayPos].cmd = cmd;
		returnStruct->sensorValues[arrayPos].sensorValue = tmpSensorvalue;	
	}	
		
	return 1;
}

long CalculateIntFromBytes(char * byteArray, int length)
{
	int i = 0;
	long result = 0;
	
	for (i = 0; i < length; ++i)
	{
		result += ((long)(*(byteArray + i))) << (length-1-i)*8;
	}
	
	return result;
}

int GetBytesFromCMD(char cmd)
{
	switch(cmd)
	{
		case TEMP_CMD:
		return 2;
		break;
		
		case ALT_CMD:
		case PRES_CMD:
		return 4;
		break;
		
		default:
		return 0;
	}
}
