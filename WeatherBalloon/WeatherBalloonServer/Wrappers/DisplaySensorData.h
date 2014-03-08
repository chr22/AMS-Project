/*
 * DisplaySensorData.h
 *
 * Created: 04-03-2014 10:29:44
 *  Author: Christian
 */ 


#ifndef DISPLAYSENSORDATA_H_
#define DISPLAYSENSORDATA_H_

//Line numbers
#define TEMP_LINE		0
#define PRES_LINE		2
#define ALT_LINE		4
#define DELTAALT_LINE	6

//cmd if three values is received
#define THREEVALUES_CMD 0x08

void WriteTemp(char* tempStr);
void WriteTempFloat(float temp);
void WritePressure(char* presStr);
void WritePressureFloat(float pres);
void WriteAltitude(char* altStr);
void WriteAltitudeFloat(float alt);
void WriteDelAltitude(char* delAlt);
void WriteDelAltitudeFloat(float delAlt);
void WriteSensorData(char* tempStr, char* presStr, char* altStr);
void WriteSensorDataFloat(float temp, float pres, float alt);
void ConvertFloatToString(float temp, char* retArray);
void ClearScreenSensorData();
void ConvertValuesToCorrectUnit(float *val, int type);

#endif /* DISPLAYSENSORDATA_H_ */