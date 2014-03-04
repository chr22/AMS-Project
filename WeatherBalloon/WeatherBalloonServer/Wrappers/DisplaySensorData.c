/*
 * DisplaySensorData.c
 *
 * Created: 04-03-2014 10:30:11
 *  Author: Christian
 */ 

#include "DisplayWrapper.h"
#include "DisplaySensorData.h"


void WriteTemp(char* tempStr)
{
	WriteToDisplay("TEMP: ");
	WriteToDisplay(tempStr);
	WriteToDisplay("*");
	NewLine();
}

void WritePressure(char* presStr)
{
	WriteToDisplay("PRES: ");
	WriteToDisplay(presStr);
	WriteToDisplay("hPa");
	NewLine();
}

void WriteAltitude(char* altStr)
{
	WriteToDisplay("ALT:  ");
	WriteToDisplay(altStr);
	WriteToDisplay("m");
	NewLine();
}

void WriteSensorData(char* tempStr, char* presStr, char* altStr)
{
	WriteTemp(tempStr);
	WritePressure(presStr);
	WriteAltitude(altStr);
}

void WriteTempFloat(float temp)
{
	char arr[6];	
	ConvertFloatToString(temp, arr);
	WriteTemp(arr);	
}

void WritePressureFloat(float pres)
{
	char arr[6];
	ConvertFloatToString(pres, arr);
	WritePressure(arr);
}

void WriteAltitudeFloat(float alt)
{
	char arr[6];
	ConvertFloatToString(alt, arr);
	WriteAltitude(arr);
}

void WriteSensorDataFloat(float temp, float pres, float alt)
{
	WriteTempFloat(temp);
	WritePressureFloat(pres);
	WriteAltitudeFloat(alt);
}

void ConvertFloatToString(float temp, char* retArray)
{
	if (temp > 0)
	{
		int intTemp = (int) temp;
		int floatTemp = (temp - (int) temp) * 100;
		
		int a = intTemp / 100;
		int b = (intTemp % 100) / 10;
		int c = (intTemp % 100) % 10;	
				
		if (a != 0)
		{
			itoa(a, retArray++, 10);	
			itoa(b, retArray++, 10);
			itoa(c, retArray++, 10);	
		}
		else if (b != 0) 
		{
			itoa(b, retArray++, 10);
			itoa(c, retArray++, 10);	
		}	
		else
		{
			itoa(c, retArray++, 10);		
		}		
		
		if (floatTemp > 0)
		{		
			*retArray = '.';
			retArray++;			
			
			int d = (floatTemp % 100) / 10;												
			itoa(d, retArray++, 10);							
						
			int e = (floatTemp % 100) % 10;						
			if (e != 0)
			{
				itoa(e, retArray++, 10);				
			}			
		}
		
		//WriteTemp(arr);		
		//return arr;
	}	
}