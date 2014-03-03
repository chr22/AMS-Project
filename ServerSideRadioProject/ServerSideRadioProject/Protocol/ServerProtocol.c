/*
 * ServerProtocol.c
 *
 * Created: 02-03-2014 17:48:09
 *  Author: Nikolaj
 */ 
#include <avr/interrupt.h>
#include "../Protocol/ServerProtocol.h"
#include "../Drivers/uart.h"
#include "../GlobalDefines.h"
#include "../Drivers/lcd162.h"


void HandleIncoming(char cmd)
{
	//SendChar(cmd);
	
	switch(cmd)
	{
		case RDY_CMD:
			HandleReadyCommand();
			LCDDispString("InsideRDY");
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
	int err = 0;
	cli();
	//SendString("HandleReady()");
	sensorID = ReadChar();
	numToRead = ReadChar();
	
	//LCDDispInteger((int)sensorID);
	//LCDDispString(" ");
	//LCDDispInteger((int)numToRead);
	err = HandleTransmission(sensorID, (int)numToRead);
		
	
	sei();
}

int HandleTransmission(char sensorID, int numToRead)
{
	int i = 0;
	int err = 0;
	char cmd = 0x00;
	MeasurementStruct *tmpMeasureStruct;
	MeasurementStruct sensorArray[numToRead];
	
	//SendChar(RDY_CMD);
	SendChar(sensorID);
	
	while((i < numToRead) && (err > 0))
	{
		cmd = ReadChar();
		HandleValueCommand(cmd, sensorID, tmpMeasureStruct);
		sensorArray[i] = *tmpMeasureStruct;
		++i;
	}
	SendAck(sensorID);
	
	LCDDispString("Done.");
	
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
	
	bytesInTransmission = GetBytesFromCMD(cmd);
	
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
