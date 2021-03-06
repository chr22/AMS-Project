/*
 * ServerProtocol.h
 *
 * Created: 02-03-2014 17:48:25
 *  Author: Nikolaj
 */ 


#ifndef SERVERPROTOCOL_H_
#define SERVERPROTOCOL_H_

typedef struct
{
	char cmd;
	char valueArray[4];
	int arrayLength;
} MeasurementStruct;

void HandleIncoming(char cmd);
int GetCommand();

int HandleValueCommand(char cmd, char sensorID, MeasurementStruct * returnStruct);
int HandleTransmission(char sensorID, int numToRead);
void HandleReadyCommand();
int GetBytesFromCMD(char cmd);
void SendAck(char sensorId);


#endif /* SERVERPROTOCOL_H_ */