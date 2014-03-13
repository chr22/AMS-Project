#ifndef GLOBALDEFINES_H_
#define GLOBALDEFINES_H_

//Error codes
#define SERVER_N_READY_ERR	-1
#define WRONG_ID_ERR		-2
#define TIMEOUT_ERR			-3
#define UNEXPECTED_CMD_ERR	-4
#define HANDLE_TRANMISSION_ERR -5


//Commands
#define TEMP_CMD 	0x11
#define ALT_CMD		0x12
#define DELALT_CMD	0x22
#define PRES_CMD	0x13
#define DELPRES_CMD	0x23
#define	ID_CMD		0x04
#define	STAT_CMD	0x05
#define ACK_CMD		0x06
#define RDY_CMD		0x07

#endif /* GLOBALDEFINES_H_ */