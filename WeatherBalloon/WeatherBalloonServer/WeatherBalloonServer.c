/*
 * WeatherBalloonServer.c
 *
 * Created: 04-03-2014 11:20:39
 *  Author: Nikolaj
 */ 


#include <avr/io.h>
#include "Wrappers/DisplaySensorData.h"

int main(void)
{	
	WriteSensorDataFloat(0.32, 432.2, 123.2112);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}