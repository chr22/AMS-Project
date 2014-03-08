/*
 * GlobalDefines.h
 *
 * Created: 25-02-2014 11:27:36
 *  Author: Nikolaj
 */ 


#ifndef GLOBALDEFINES_H_
#define GLOBALDEFINES_H_

//Error codes
#define SERVER_N_READY_ERR	-1
#define WRONG_ID_ERR		-2
#define TIMEOUT_ERR			-3
#define UNEXPECTED_CMD_ERR	-4

//Commands
#define TEMP_CMD 	0x01
#define ALT_CMD		0x02
#define PRES_CMD	0x03
#define THREEVALUES_CMD 0x08
#define	ID_CMD		0x04
#define	STAT_CMD	0x05
#define ACK_CMD		0x06
#define RDY_CMD		0x07

//Line numbers
#define TEMP_LINE	0
#define PRES_LINE	2
#define ALT_LINE	4

//Utility values
#define SOURCE_ID	0x20

#endif /* GLOBALDEFINES_H_ */