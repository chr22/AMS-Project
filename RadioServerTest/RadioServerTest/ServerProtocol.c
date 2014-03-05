/*
 * ServerProtocol.c
 *
 * Created: 02-03-2014 17:48:09
 *  Author: Nikolaj
 */ 
#include <avr/interrupt.h>
#include "ServerProtocol.h"
#include "uart.h"
#include "GlobalDefines.h"
#include "lcd162.h"


void HandleIncoming(char cmd)
{
	switch(cmd)
	{
		case RDY_CMD:
			HandleReadyCommand();
			break;
			
		case TEMP_CMD:
		case PRES_CMD:
		case ID_CMD:
		case ALT_CMD:
			//HandleValueCommand(cmd);
			//break;
			
		default:
			break;
			//Unknown command
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
	
	LCDDispInteger((int)sensorID);
	LCDDispString(" ");
	LCDDispInteger((int)numToRead);
	
	
	SendChar(0x20);
	
	firstCommand = ReadChar();
	LCDDispInteger((int)firstCommand);
	
	//err = HandleTransmission(sensorID, (int)numToRead);
		
	
	sei();
}

int HandleTransmission(char sensorID, int numToRead)
{
	int i = 0;
	char cmd = 0x00;
	
	MeasurementStruct tmpMeasureStruct;
	//MeasurementStruct sensorArray[numToRead];
	//LCDClear();
	//LCDDispInteger(numToRead);
	while(i < numToRead)
	{
		cmd = ReadChar();
		++i;
		LCDClear();
		LCDDispInteger(i);
		HandleValueCommand(cmd, sensorID, &tmpMeasureStruct);
		
	}
	
	SendAck(sensorID);
	
	LCDDispString("Cmd: ");
	LCDDispInteger((int)cmd);
	LCDDispString(" Len: ");
	LCDDispInteger(tmpMeasureStruct.arrayLength);
			
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
	
	return 1;
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
