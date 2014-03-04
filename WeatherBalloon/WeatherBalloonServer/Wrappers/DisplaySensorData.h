/*
 * DisplaySensorData.h
 *
 * Created: 04-03-2014 10:29:44
 *  Author: Christian
 */ 


#ifndef DISPLAYSENSORDATA_H_
#define DISPLAYSENSORDATA_H_

void WriteTemp(char* tempStr);
void WriteTempFloat(float temp);
void WritePressure(char* presStr);
void WritePressureFloat(float pres);
void WriteAltitude(char* altStr);
void WriteAltitudeFloat(float alt);
void WriteSensorData(char* tempStr, char* presStr, char* altStr);
void WriteSensorDataFloat(float temp, float pres, float alt);
void ConvertFloatToString(float temp, char* retArray);


#endif /* DISPLAYSENSORDATA_H_ */