/*
 * DefinesServer.h
 *
 * Created: 09-03-2014 00:53:13
 *  Author: Casper
 */ 


#ifndef DEFINESSENSOR_H_
#define DEFINESSENSOR_H_

#undef ATMEGA32_DEV
//#define ATMEGA32_DEV True

#ifdef ATMEGA32_DEV
#define F_CPU 3686400
#else
#define F_CPU 16000000
#endif

#endif /* DEFINESSENSOR_H_ */