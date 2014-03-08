/*
 * ServerProtocol.h
 *
 * Created: 02-03-2014 17:48:25
 *  Author: Nikolaj
 */ 


#ifndef SERVERPROTOCOL_H_
#define SERVERPROTOCOL_H_

#define RADIO_TIMEOUT_MS 3000

typedef struct
{
	char cmd;
	int numberOfValues;
	//char valueArray[4];
	long arrayLength;
	long tempValue;
	long presValue;
	long altiValue;
	long delAltValue;
} MeasurementStruct;

int HandleIncoming(char cmd);
int GetCommand();

int HandleValueCommand(char cmd, char sensorID, MeasurementStruct * returnStruct);
int HandleTransmission(char sensorID, int numToRead);
int HandleReadyCommand();
int GetBytesFromCMD(char cmd);
void SendAck(char sensorId);
long CalculateIntFromBytes(char * byteArray, int length);
int SendToDisplay(MeasurementStruct *  sensorStruct);

#endif /* SERVERPROTOCOL_H_ */