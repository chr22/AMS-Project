#ifndef DEFINESSENSOR_H_
#define DEFINESSENSOR_H_

#undef ATMEGA32_DEV
//#define ATMEGA32_DEV True

#define RoutineFrequenzy 10000

#ifdef ATMEGA32_DEV
#define F_CPU 3686400
#else
#define F_CPU 16000000
#endif

#endif /* DEFINESSENSOR_H_ */