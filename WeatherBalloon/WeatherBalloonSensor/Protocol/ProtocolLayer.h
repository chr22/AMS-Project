/*
 * ProtocolLayer.h
 *
 * Created: 28-02-2014 10:36:56
 *  Author: Nikolaj
 */ 


#ifndef PROTOCOLLAYER_H_
#define PROTOCOLLAYER_H_


//Waits for the ServerReadyToReceive command
int WaitForServerReady(int timeOutMs, unsigned char id);

//Transmits measurement type and value (And length?)
int TransmitMeasurement(char measureType, long measureVal, char id);

int WaitForAck(int timeOutMs, unsigned char id);

#endif /* PROTOCOLLAYER_H_ */