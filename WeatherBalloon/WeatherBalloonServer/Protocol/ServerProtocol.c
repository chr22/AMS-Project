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
#include "../Drivers/lcd162.h"


void HandleIncoming(char cmd)
{
	//SendChar(cmd);
	
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
	
	//Debugging chars
	unsigned int tmp_temp = 0x00;
	char tmp_id = 0x00;
	char tmp_cmd = 0x00;
	char tmp_arr[2];
	char test  = 0x01;
	
	tmp_arr[0] = 0x01;
	tmp_arr[1] = 0x10;
	
	MeasurementStruct tmpMeasureStruct;
	MeasurementStruct sensorArray[numToRead];
	
	//SendChar(RDY_CMD);
	SendChar(sensorID);
	
	while(i < numToRead)
	{
		cmd = ReadChar();
		HandleValueCommand(cmd, sensorID, &tmpMeasureStruct);
		tmp_temp = (unsigned int)(tmpMeasureStruct.valueArray[0] << 8) + (tmpMeasureStruct.valueArray[1]);
		//tmp_temp = (unsigned int)tmpMeasureStruct.arrayLength;
		//tmp_temp = (unsigned int)test;
		sensorArray[i] = tmpMeasureStruct;
		++i;
	}
	SendAck(sensorID);
	
	//tmp_temp = 20;
	tmp_cmd = cmd;
	tmp_id	= sensorID;
	
	//tmp_temp = (unsigned int)((sensorArray[0].valueArray[0] << 8) + (sensorArray[0].valueArray[1]));
	//tmp_temp = (unsigned int)((tmp_arr[0] << 8) + (tmp_arr[1]));
	LCDClear();
	LCDDispString("ID: ");
	LCDDispInteger((int)tmp_id);
	LCDDispString("  ");
	LCDDispInteger((unsigned int)tmp_temp);
	
	
	//LCDClear();
	
	
	
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
	
	//Debug
	bytesInTransmission = 2;
	
	(*returnStruct).cmd = cmd;
	(*returnStruct).arrayLength = bytesInTransmission;
	
	for (i = 0; i < bytesInTransmission; ++i )
	{
		(*returnStruct).valueArray[i] = ReadChar();
	}	
	
	//For debugging
	//(*returnStruct).valueArray[0] = 0x01;
	//(*returnStruct).valueArray[1] = 0x10;
	
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
