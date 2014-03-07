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
	char firstCommand = 0x00;
	
	int err = 0;
	//cli();
	//SendChar(0x80);
	sensorID = ReadChar();
	numToRead = ReadChar();
		
	//Send server ready
	SendChar(sensorID);
	
	err = HandleTransmission(sensorID, (int)numToRead);
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
		err = SendToDisplay(&tmpMeasureStruct);
	}
	
	SendAck(sensorID);
			
	return err;
}

int SendToDisplay(MeasurementStruct * sensorStruct)
{
	
	switch(sensorStruct->cmd)
	{
		case TEMP_CMD:
			//Call Temp
			WriteTempFloat(sensorStruct->sensorValue);
			break;
		case ALT_CMD:
			//Call Alt
			WriteAltitudeFloat(sensorStruct->sensorValue);
			break;
		case PRES_CMD:
			//Call Pres
			WritePressureFloat(sensorStruct->sensorValue);
			break;
		default:
			WriteToDisplay("1234");
			NewLine();
			break;			
	}
	
	//Call Display functions here..	
	
	//LCDDispString("Len: ");
	//LCDDispInteger(sensorStruct->arrayLength);
	//LCDDispString(" Val: ");
	//LCDDispInteger(sensorStruct->sensorValue);
	//LCDGotoXY(0,1);
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
	(*returnStruct).arrayLength = bytesInTransmission;
	
	for (i = 0; i < bytesInTransmission; ++i )
	{
		(*returnStruct).valueArray[i] = ReadChar();
	}	
	
	(*returnStruct).sensorValue = CalculateIntFromBytes((*returnStruct).valueArray, bytesInTransmission);
	
	return 1;
}

int CalculateIntFromBytes(char * byteArray, int length)
{
	int i = 0;
	int result = 0;
	
	for (i = 0; i < length; ++i)
	{
		result += ((int)(*(byteArray + i))) << (length-1-i)*8;
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
