#define PARAM_MG      3038        /*calibration parameter */
#define PARAM_MH     -7357        /*calibration parameter */
#define PARAM_MI      3791        /*calibration parameter */

void BMP180_Init(long BaseLevelPressure);
unsigned char BMP180_GetDeviceId();
long BMP180_GetTemperature();
long BMP180_GetPressure();
long BMP180_GetDeltaPressure();
long BMP180_GetAltitude();
long BMP180_GetDeltaAltitude();

/* this structure holds all device specific calibration parameters */
struct bmp180_calibration_params{
	short ac1;
	short ac2;
	short ac3;
	unsigned short ac4;
	unsigned short ac5;
	unsigned short ac6;
	short b1;
	short b2;
	short mb;
	short mc;
	short md;
	long param_b5;
	short oversampling_setting;
};