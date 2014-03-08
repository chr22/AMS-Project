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

int PerformFullTransmission(char id, struct DataValue_Params data_params[]);
int TemperatureSend(char temp[]);
int DataReady(char id, char numToTransmit);
//int WaitForAck(int timeOutMs);


int AltitudeSend (char alt[]);
int PressureSend(char pres[]);
int StationIDSend(char id);
int StatusSend(char status[]);


	struct DataValue_Params {
		unsigned char DataCommand;
		long DataValue;
	};



#endif /* RADIOSOURCE_H_ */