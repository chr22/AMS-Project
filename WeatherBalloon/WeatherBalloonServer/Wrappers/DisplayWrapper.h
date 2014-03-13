/*
 * DisplayWrapper.h
 *
 * Created: 03-03-2014 17:04:31
 *  Author: Christian Svejstrup
 */ 

#include "../Drivers/DEM128064A.h"

#ifndef DISPLAYWRAPPER_H_
#define DISPLAYWRAPPER_H_

void DisplayWrapper_WriteToDisplay(char* dispStr);
void DisplayWrapper_NewLine();
void DisplayWrapper_SetLine(int line);
void DisplayWrapper_SetPosition(int pos);
void DisplayWrapper_ClearScreen();


#endif /* DISPLAYWRAPPER_H_ */