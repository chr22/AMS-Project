/*
 * RadioSource.h
 *
 * Created: 25-02-2014 10:16:03
 *  Author: Nikolaj
 */ 


#ifndef RADIOSOURCE_H_
#define RADIOSOURCE_H_

/*
*	Command Specifications
*/
#define TEMP_CMD 	0x01
#define ALT_CMD		0x02
#define PRES_CMD	0x03
#define	ID_CMD		0x04
#define	STAT_CMD	0x05

/*
*	Constant Defines
*/
#define	FULL_TRANSMIT_NUM	0x03
#define RADIO_TIMEOUT_MS	5000

int PerformFullTransmission(char id, char * temp, char * alt, char * pres);
int TemperatureSend(char *);
int DataReady(char id, int numToTransmit);
int WaitForServerReady(int timeOutMs);
int WaitForAck(int timeOutMs);


int AltitudeSend (char * alt);
int PressureSend(char * pres);
int StationIDSend(char id);
int StatusSend(char * status);


#endif /* RADIOSOURCE_H_ */