/*
 * DisplayWrapper.h
 *
 * Created: 03-03-2014 17:04:31
 *  Author: Christian Svejstrup
 */ 

#include "../Drivers/dem128064a.h"

#ifndef DISPLAYWRAPPER_H_
#define DISPLAYWRAPPER_H_

void WriteToDisplay(char* dispStr);
void NewLine();
void SetLine(int line);
void SetPosition(int pos);
void ClearScreenWrapper();


#endif /* DISPLAYWRAPPER_H_ */