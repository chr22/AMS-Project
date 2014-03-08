/*
 * ServerProtocol.c
 *
 * Created: 02-03-2014 17:48:09
 *  Author: Nikolaj
 */ 
#include <avr/interrupt.h>
#include "../Protocol/ServerProtocol.h"
#include "../Drivers/uart.h"
#include "../Util/GlobalDefines.h"

#include "../Wrappers/DisplaySensorData.h"
#include "../Wrappers/DisplayWrapper.h"


void HandleIncoming(char cmd)
{
	if(cmd == RDY_CMD)
	{
		HandleReadyCommand();
	}
}

void HandleReadyCommand()
{
	char sensorID, numToRead;
	//char firstCommand = 0x00;
	
	int err = 0;
	//cli();
	//SendChar(0x80);
	sensorID = ReadChar();
	numToRead = ReadChar();
		
	//Send server ready
	SendChar(sensorID);
	
	err = HandleTransmission(sensorID, (int)numToRead);
	
	if (err)
	{
		//do stuff
	}
	
	sei();
}

int HandleTransmission(char sensorID, int numToRead)
{
	int i = 0;
	int err = 0;
	char cmd = 0x00;
	
	MeasurementStruct tmpMeasureStruct;
	//MeasurementStruct sensorArray[numToRead];
	
	//ClearScreenSensorData();
	
	while(i < numToRead)
	{
		cmd = ReadChar();
		++i;
		HandleValueCommand(cmd, sensorID, &tmpMeasureStruct);		
	}
	
	SendAck(sensorID);
	
	if (numToRead >= 3)
	{
		tmpMeasureStruct.cmd = THREEVALUES_CMD;
	}	
	
	err = SendToDisplay(&tmpMeasureStruct);
			
	return err;
}

int SendToDisplay(MeasurementStruct * sensorStruct)
{
	
	switch(sensorStruct->cmd)
	{
		case TEMP_CMD:
			SetLineNum(TEMP_LINE);
			WriteTempFloat(sensorStruct->tempValue);
			break;
		case ALT_CMD:
			SetLineNum(ALT_LINE);
			WriteAltitudeFloat(sensorStruct->altiValue);
			break;
		case PRES_CMD:
			SetLineNum(PRES_LINE);
			WritePressureFloat(sensorStruct->presValue);
			break;
		case THREEVALUES_CMD:
			ClearScreenSensorData();
			WriteSensorDataFloat(sensorStruct->tempValue, sensorStruct->presValue, sensorStruct->altiValue);
			break;
		default:
			WriteToDisplay("1234");
			NewLine();
			break;			
	}	
	
	return 1;
}

void SendAck(char sensorID)
{
	SendChar(ACK_CMD);
	SendChar(sensorID);
}

int HandleValueCommand( char cmd, char sensorID, MeasurementStruct * returnStruct )
{
	int bytesInTransmission = 0;
	int i = 0;
	
	//First byte after command is length field
	bytesInTransmission = (int)ReadChar();
	
	(*returnStruct).cmd = cmd;
	//(*returnStruct).arrayLength = bytesInTransmission;
	
	char sensorValue[bytesInTransmission];
	
	for (i = 0; i < bytesInTransmission; ++i )
	{
		sensorValue[i] = ReadChar();
	}	
	
	long tmpSensorvalue = CalculateIntFromBytes(sensorValue, bytesInTransmission);
	
	if (cmd == TEMP_CMD)
	{
		returnStruct->tempValue = tmpSensorvalue;
	}
	else if (cmd == PRES_CMD)
	{
		returnStruct->presValue = tmpSensorvalue;
	}
	else if (cmd == ALT_CMD)
	{
		returnStruct->altiValue = tmpSensorvalue;
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
