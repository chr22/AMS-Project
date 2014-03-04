#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>
//#include "Drivers/DEM128064A.h"
#include "DisplayWrapper.h"
#include "DisplaySensorData.h"

int main()
{
  WriteTemp("23");
  WritePressure("653");
  WriteAltitude("900");
  NewLine();
  WriteSensorData("123", "456", "789");
  
  while(1)
  {}
}