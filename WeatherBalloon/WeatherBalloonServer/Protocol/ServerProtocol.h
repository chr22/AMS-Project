/*
 * ServerProtocol.h
 *
 * Created: 02-03-2014 17:48:25
 *  Author: Nikolaj
 */ 


#ifndef SERVERPROTOCOL_H_
#define SERVERPROTOCOL_H_

#define RADIO_TIMEOUT_MS 3000
#define MAX_NUM_OF_SENSORVALUES 4

typedef struct
{
	char cmd;
	long sensorValue;
} SensorStruct;

typedef struct
{
	SensorStruct sensorValues[MAX_NUM_OF_SENSORVALUES];
} MeasurementStruct;


int HandleIncoming(char cmd);
int GetCommand();

int HandleValueCommand(char cmd, char sensorID, MeasurementStruct * returnStruct, int arrayPos);
int HandleTransmission(char sensorID, int numToRead);
int HandleReadyCommand();
int GetBytesFromCMD(char cmd);
void SendAck(char sensorId);
long CalculateIntFromBytes(char * byteArray, int length);
int SendToDisplay(MeasurementStruct *  sensorStruct, int numberOfValues);

#endif /* SERVERPROTOCOL_H_ */