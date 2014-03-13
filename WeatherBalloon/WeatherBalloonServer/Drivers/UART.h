void InitUART(unsigned long BaudRate, unsigned char DataBit);
unsigned char CharReady();
char ReadChar();
void SendChar(char Ch);
void SendString(char* String);
void SendInteger(int Number);
int ReadCharWTimeout(char * retVal, int timeOutMs);
