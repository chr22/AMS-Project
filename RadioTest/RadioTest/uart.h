/**************************************
* "uart.h":                           *
* Header file for Mega32 UART driver. *
* Henning Hargaard, 1/11 2011         *
***************************************/
#define XTAL 16000000
//#define F_CPU XTAL

void InitUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char CharReady();
char ReadChar();
void SendChar(char Ch);
void SendString(char* String);
void SendInteger(int Number);

//Our defined functions
int ReadCharWTimeout(char * retVal, int timeOutMs);
int ServerResponse(char moduleId, int timeoutMS);

//char readyReg;

/**************************************/
