void I2C_Init();
void I2C_Start();
void I2C_Write(unsigned char data);
unsigned char I2C_Read (unsigned char isLast);
void I2C_Stop();	
void I2C_RepeatedStart();