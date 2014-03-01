/*
 * ProtocolLayer.h
 *
 * Created: 28-02-2014 10:36:56
 *  Author: Nikolaj
 */ 


#ifndef PROTOCOLLAYER_H_
#define PROTOCOLLAYER_H_


//Waits for the ServerReadyToReceive command
int WaitForServerReady(int timeOutMs);

//Transmits measurement type and value (And length?)
int TransmitMeasurement(char measureType, int measureVal);

int WaitForAck(int timeOutMs);

#endif /* PROTOCOLLAYER_H_ */