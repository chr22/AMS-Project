#ifndef PROTOCOLLAYER_H_
#define PROTOCOLLAYER_H_

//Sends the ready command
int DataReady(char id, int numToTransmit);

//Waits for the ServerReadyToReceive command
int WaitForServerReady(int timeOutMs, unsigned char id);

//Transmits measurement type and value
int TransmitMeasurement(char measureType, long measureVal, char id);

//Waits for Acknowledge command from server
int WaitForAck(int timeOutMs, unsigned char id);

#endif /* PROTOCOLLAYER_H_ */