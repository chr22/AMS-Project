/*
 * DisplaySensorData.c
 *
 * Created: 04-03-2014 10:30:11
 *  Author: Christian
 */ 

#include "DisplayWrapper.h"
#include "DisplaySensorData.h"
#include "../../WeatherBalloonCommon/GlobalDefines.h"
#include "stdlib.h"


void WriteTemp(char* tempStr)
{
	DisplayWrapper_WriteToDisplay("TEMP: ");
	DisplayWrapper_WriteToDisplay(tempStr);
	DisplayWrapper_WriteToDisplay("*C");
	DisplayWrapper_NewLine();
}

void WritePressure(char* presStr)
{
	DisplayWrapper_WriteToDisplay("PRES: ");
	DisplayWrapper_WriteToDisplay(presStr);
	DisplayWrapper_WriteToDisplay("hPa");
	DisplayWrapper_NewLine();
}

void WriteAltitude(char* altStr)
{
	DisplayWrapper_WriteToDisplay("ALT:  ");
	DisplayWrapper_WriteToDisplay(altStr);
	DisplayWrapper_WriteToDisplay("m");
	DisplayWrapper_NewLine();
}

void WriteDelAltitude(char* delAlt)
{
	DisplayWrapper_WriteToDisplay("dALT: ");
	DisplayWrapper_WriteToDisplay(delAlt);
	DisplayWrapper_WriteToDisplay("m");
	DisplayWrapper_NewLine();
}

void WriteSensorData(char* tempStr, char* presStr, char* altStr)
{
	WriteTemp(tempStr);
	WritePressure(presStr);
	WriteAltitude(altStr);
}

void WriteTempFloat(float temp)
{
	char arr[7];		
	ConvertValuesToCorrectUnit(&temp, TEMP_CMD);
	ConvertFloatToString(temp, arr);
	WriteTemp(arr);	
}

void WritePressureFloat(float pres)
{
	char arr[7];
	ConvertValuesToCorrectUnit(&pres, PRES_CMD);
	ConvertFloatToString(pres, arr);
	WritePressure(arr);
}

void WriteAltitudeFloat(float alt)
{
	char arr[7];
	ConvertValuesToCorrectUnit(&alt, ALT_CMD);
	ConvertFloatToString(alt, arr);
	WriteAltitude(arr);
}

void WriteDelAltitudeFloat(float delAlt)
{
	char arr[7];
	ConvertValuesToCorrectUnit(&delAlt, DELALT_CMD);
	ConvertFloatToString(delAlt, arr);
	WriteDelAltitude(arr);
}

void WriteSensorDataFloat(float temp, float pres, float alt)
{
	WriteTempFloat(temp);
	DisplayWrapper_NewLine();
	WritePressureFloat(pres);
	DisplayWrapper_NewLine();
	WriteAltitudeFloat(alt);
}

void ConvertFloatToString(float temp, char* retArray)
{
	if (temp > 0)
	{
		int intTemp = (int) temp;
		int floatTemp = (temp - (int) temp) * 100;
		
		int thousands = intTemp / 1000;
		intTemp %= 1000;
		int hundreds = intTemp / 100;
		int tens = (intTemp % 100) / 10;
		int ones = (intTemp % 100) % 10;	
						
		if (thousands != 0)
		{
			itoa(thousands, retArray++, 10);
		}	
		else {
			*retArray = ' ';
			retArray++;
		}	
		if (hundreds != 0 || thousands != 0)
		{
			itoa(hundreds, retArray++, 10);	
			itoa(tens, retArray++, 10);
			itoa(ones, retArray++, 10);	
		}
		else if (tens != 0) 
		{
			*retArray = ' ';
			retArray++;
			itoa(tens, retArray++, 10);
			itoa(ones, retArray++, 10);	
		}	
		else
		{
			*retArray = ' ';
			retArray++;
			*retArray = ' ';
			retArray++;
			itoa(ones, retArray++, 10);		
		}		
		
		if (floatTemp > 0)
		{		
			*retArray = '.';
			retArray++;			
			
			int d = (floatTemp % 100) / 10;												
			itoa(d, retArray++, 10);							
						
			int e = (floatTemp % 100) % 10;						
			
			itoa(e, retArray++, 10);										
		}
		else 
		{
			*retArray = '.';
			retArray++;
			*retArray = '0';
			retArray++;
			*retArray = '0';
			retArray++;
		}
	}
	else
	{
		*retArray = ' ';
		retArray++;
		*retArray = ' ';
		retArray++;
		*retArray = ' ';
		retArray++;
		*retArray = '0';
		retArray++;
		*retArray = '.';
		retArray++;
		*retArray = '0';
		retArray++;
		*retArray = '0';
		retArray++;
	}	
}

void ClearScreen()
{
	DisplayWrapper_ClearScreen();
}

void ConvertValuesToCorrectUnit(float *val, int type) 
{
	if (type == TEMP_CMD)
	{
		*val /= 10.0;
	}
	else if(type == ALT_CMD)
	{
		*val /= 1.0;
	}
	else if(type == PRES_CMD)
	{
		*val /= 100.0;
	}
	else if(type == DELALT_CMD)
	{
		*val /= 1.0;
	}
}

void SetLine(int line)
{
	DisplayWrapper_SetLine(line);
}

void SetPosition(int pos)
{
	DisplayWrapper_SetPosition(pos);	
}