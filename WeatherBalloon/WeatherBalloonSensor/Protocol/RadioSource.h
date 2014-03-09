/*
 * RadioSource.h
 *
 * Created: 25-02-2014 10:16:03
 *  Author: Nikolaj
 */ 


#ifndef RADIOSOURCE_H_
#define RADIOSOURCE_H_

/*
*	Constant Defines
*/
#define	FULL_TRANSMIT_NUM	0x03
#define RADIO_TIMEOUT_MS	5000

struct DataValue_Params {
	unsigned char DataCommand;
	long DataValue;
};


int PerformFullTransmission( char id, struct DataValue_Params* data_params, int params_count );
int DataReady(char id, int numToTransmit);
//int WaitForAck(int timeOutMs);

int TemperatureSend(char temp[]);
int AltitudeSend (char alt[]);
int PressureSend(char pres[]);
int StationIDSend(char id);
int StatusSend(char status[]);



#endif /* RADIOSOURCE_H_ */