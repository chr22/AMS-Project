#define XTAL 16000000


void InitUART(unsigned long BaudRate, unsigned char DataBit);
void SendChar(char Ch);
int ReadCharWTimeout(char * retVal, int timeOutMs);

