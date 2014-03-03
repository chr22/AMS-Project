
/*
  PRELIMINARY TEST PROGRAM FOR DM128064A Graphic Display Module
  AVR GCC version
  
  Henning Hargaard February 5, 2014. 
  
*/

// Max crystal frequency = 16 MHz => T = 62 ns

#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>
#include "Drivers/DEM128064A.h"
#include "DisplayWrapper.h"

int main()
{  
  WriteToDisplay("1337");
  WriteToDisplay("2579");
      
  while(1)
  {}
}