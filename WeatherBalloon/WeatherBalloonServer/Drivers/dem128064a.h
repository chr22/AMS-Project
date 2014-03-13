#ifndef GRAPHICdefine
#define GRAPHICdefine

#define DATA_OUT     PORTA
#define DATA_IN      PINA
#define DATA_DDR     DDRA

#define CONTROL_PORT PORTC
#define CONTROL_DDR  DDRC

// Initialized the display module
void DEM128064A_DisplayInit();
// Turns on the display module (both left and right halfes)
void DEM128064A_DisplayOn();
// Turns off the display module (both left and right halfes)
void DEM128064A_DisplayOff();
// Blanks the display (both left and right halfes)
void DEM128064A_ClearScreen();
// Sets one pixel at (x,y)
// "x" is the horizontal coordinate (starting at the LCD left side)
// "y" is the vertical coordinate (starting at the LCD bottom side)
void DEM128064A_SetPixel(unsigned char x, unsigned char y);
// Fills the (whole) display with a predefined bit pattern
// "picArray" is a pointer to the bit pattern array prestored in flash memory
void DEM128064A_DisplayPic(const char *picArray);
void DEM128064A_DisplayCharArray(const char *disArray, int length);
// Manuel position and line
void DEM128064A_SetNextChar(const char *nextChar, int position, int line);
// Auto increments the line and position
void DEM128064A_SetNextCharAuto(const char *nextChar);
// Valid values: 0-7
void DEM128064A_SetLineNum(int line);
// Valid values: 0-127
void DEM128064A_SetPositionNum(int pos);
// Valid values: 0-15
void DEM128064A_SetCharPosition(int pos);
// Sets cursor to next line and resets cursor to start of display
void DEM128064A_NewLine();
// Draws a horizontal line at the display
// "StartX" and "StartY" is the leftmost start point for the line
// "Length" is the line length measured in pixels
void DEM128064A_Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length);

#endif 
//----------------------------------------------------------------------