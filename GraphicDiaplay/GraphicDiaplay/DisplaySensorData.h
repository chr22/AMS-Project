/*
 * DisplaySensorData.h
 *
 * Created: 04-03-2014 10:29:44
 *  Author: Christian
 */ 


#ifndef DISPLAYSENSORDATA_H_
#define DISPLAYSENSORDATA_H_

void WriteTemp(char* tempStr);
void WritePressure(char* presStr);
void WriteAltitude(char* altStr);
void WriteSensorData(char* tempStr, char* presStr, char* altStr);


#endif /* DISPLAYSENSORDATA_H_ */