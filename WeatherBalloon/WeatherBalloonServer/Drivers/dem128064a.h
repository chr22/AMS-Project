/*----------------------------------------------------------------------
File name: "DEM128064A.h"

Description: Driver for Graphic Display LCD Module DEM128064A.

Author: Henning Hargaard
Date: 5.2.2014
-----------------------------------------------------------------------*/
#ifndef GRAPHICdefine
#define GRAPHICdefine

#define DATA_OUT     PORTA
#define DATA_IN      PINA
#define DATA_DDR     DDRA

#define CONTROL_PORT PORTC
#define CONTROL_DDR  DDRC

// Initialized the display module
void DisplayInit();
// Turns on the display module (both left and right halfes)
void DisplayOn();
// Turns off the display module (both left and right halfes)
void DisplayOff();
// Blanks the display (both left and right halfes)
void ClearScreen();
// Sets one pixel at (x,y)
// "x" is the horizontal coordinate (starting at the LCD left side)
// "y" is the vertical coordinate (starting at the LCD bottom side)
void SetPixel(unsigned char x, unsigned char y);
// Fills the (whole) display with a predefined bit pattern
// "picArray" is a pointer to the bit pattern array prestored in flash memory
void DisplayPic(const char *picArray);
void DisplayCharArray(const char *disArray, int length);
// Manuel position and line
void SetNextChar(const char *nextChar, int position, int line);
// Auto increments the line and position
void SetNextCharAuto(const char *nextChar);
// Valid values: 0-7
void SetLineNum(int line);
// Valid values: 0-127
void SetPositionNum(int pos);
// Valid values: 0-15
void SetCharPosition(int pos);
// Sets cursor to next line and resets cursor to start of display
void NextLine();
// Draws a horizontal line at the display
// "StartX" and "StartY" is the leftmost start point for the line
// "Length" is the line length measured in pixels
void Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length);
#endif 
//----------------------------------------------------------------------