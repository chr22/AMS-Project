/*
  Display Driver for Graphic Display Module DEM128064A.
   
  IMPORTANT: The functions DisplayRead() and WaitBusy()
             are not working. The BUSY bit always reads as 1.
             However, it is not necessary to wait for the busy flag.
  
  Author: Henning Hargaard
  Date: 5.2.2014
*/  

#include <avr/io.h> 
#include <avr/cpufunc.h>
#define F_CPU 3686400
#include <util/delay.h>
#include "DEM128064A.h"

// Control port pin definitions:
#define CS2  7
#define CS1  6
#define RSTB 5
#define RW   2
#define E    1
#define RS   0

#define LEFT  0
#define RIGHT 1

#define CONTROL 0
#define DATA    1

// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

// Writes a byte to the display
// "Chip" = LEFT or RIGHT
// "Data" = 8 bit data to be written
// "Type" = CONTROL" or "DATA"
void DisplayWrite(unsigned char Chip, unsigned char Data, unsigned char Type)
{
  // Set up "RS" (according to "Type")
  if (Type == DATA)
    CONTROL_PORT |= (1<<RS);
  else
    CONTROL_PORT &= ~(1<<RS);  	
  // Data port = Outputs
  DATA_DDR = 0xFF;
  // Set up the data
  DATA_OUT = Data;
  // Select "writing"
  CONTROL_PORT &= ~(1<<RW);
  // Select the actual chip (LEFT or RIGHT)
  if (Chip == LEFT)
    CONTROL_PORT |= (1<<CS1);
  else
    CONTROL_PORT |= (1<<CS2);
  // tASU = min 140 ns (3T)
  // ( tWL = min 450 ns (8T) )
  _NOP();
  _NOP();
  _NOP();
  // Start writing    
  CONTROL_PORT |= (1<<E);  
  // tWH = min 450 ns (8T)
  // tDSU = min 200 ns (4T)
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  // Stop writing   
  CONTROL_PORT &= ~(1<<E);  
  // tAH = min 10 ns (1T)
  // tDHW = min 10 ns (1T)
  _NOP();
  CONTROL_PORT |= (1<<RW);  
  // Deselect both chips 
  CONTROL_PORT &= ~(1<<CS1);  
  CONTROL_PORT &= ~(1<<CS2);  
  // Data port = Inputs (can be omitted) 
  DATA_DDR = 0;
  // ( tc = min 1000 ns (16T) OK )
}

// Reads a byte from the display
// "Chip" = LEFT or RIGHT
// "Type" = CONTROL" or "DATA"
unsigned char DisplayRead(unsigned char Chip, unsigned char Type)
{
unsigned char tmp;

  // Set up "RS" (according to "Type")
  if (Type == DATA)
    CONTROL_PORT |= (1<<RS);
  else
    CONTROL_PORT &= ~(1<<RS);
  // Select "Reading"
  CONTROL_PORT |= (1<<RW);
  // Data port = Inputs  
  DATA_DDR = 0x00;
  // Select the actual chip (LEFT or RIGHT)  
  if (Chip == LEFT)
    CONTROL_PORT |= (1<<CS1);
  else
    CONTROL_PORT |= (1<<CS2);
  // tASU = min 140 ns (3T)
  // ( tWL = min 450 ns (8T) )
  _NOP();
  _NOP();
  _NOP();
  // Start reading  
  CONTROL_PORT |= (1<<E);
  // tWH = min 450 ns (8T)
  // tDS = max 320 ns (6T)
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  // Read data from data bus
  tmp = DATA_IN;
  _NOP();
  // Deselect both chips
  CONTROL_PORT &= ~(1<<CS1);
  CONTROL_PORT &= ~(1<<CS2);
  // Stop reading (important to do this AFTER deselecting the chips!)
  CONTROL_PORT &= ~(1<<E);   
  // ( tAH = min 10 ns (1T) OK )
  // ( tDRH = min 20 ns (1T) OK )
  // ( tc = min 1000 ns (16T) OK )
  // ( tWL = min 450 ns (8T) OK )
  // Return the previously read data 
  return tmp;
}

// Set the display Y address counter (left or right chip)
// "Chip" = LEFT or RIGHT
// "Y" = 0-63
void SetY(unsigned char Chip, unsigned char Y)
{
  if (Y < 64)
    DisplayWrite( Chip, (0b01000000 | Y), CONTROL);
}

// Set the display page number (left or right chip)
// "Chip" = LEFT or RIGHT
// "Page" = 0-7
void SetPage(unsigned char Chip, unsigned char Page)
{
  if (Page < 8)
    DisplayWrite( Chip, (0b10111000 | Page), CONTROL);
}

// Sets the display start line (only used for display scroling)
// "Chip" = LEFT or RIGHT
// "StartLinePage = 0-63
void SetStartLine(unsigned char Chip, unsigned char StartLine)
{
  if (StartLine < 64)
    DisplayWrite( Chip, (0b11000000 | StartLine), CONTROL);
}

// Reads and returns the display status byte (left or right chip)
// "Chip" = LEFT or RIGHT
unsigned char Status(unsigned char Chip)
{
unsigned char tmp;

  tmp = DisplayRead(Chip, CONTROL);
  return tmp;
}

// Waits for the busy flag to go low
// "Chip" = LEFT or RIGHT
// NOTICE: DOES NOT WORK PROPERLY (BUSY flag is always 1)
void WaitBusy(unsigned char Chip)
{
  while ( DisplayRead(Chip, CONTROL) & 0b10000000 )
  {}
}

// Clears all pixels at one of the screens halfes (left or right)
// "Chip" = LEFT or RIGHT
void ClearHalfScreen(unsigned char Chip)
{
unsigned char i, j;

  for (i=0; i<8; i++)
  {
    SetPage(Chip,i);
    SetY(Chip,0);
    for (j= 0; j<64; j++)
      DisplayWrite(Chip, 0, DATA);
  }
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
  // Data port is input
  DATA_DDR = 0;
  // Control port is output
  CONTROL_DDR = 0xFF;
  // Set up the initial control signals
/*  E = 0;
  CS1 = 0;
  CS2 = 0;
  RW = 1;
  RS = 1; */
  CONTROL_PORT &= ~(1<<E);   // E = 0
  CONTROL_PORT &= ~(1<<CS1); // CS1 = 0  
  CONTROL_PORT &= ~(1<<CS2); // CS21 = 0 
  CONTROL_PORT |= (1<<RW);   // RW = 1
  CONTROL_PORT |= (1<<RS);   // RS = 1
  // Start the RESET pulse
//  RSTB = 0;
  CONTROL_PORT &= ~(1<<RSTB); // RSTB = 0
  // Wait 200 ms
  _delay_ms(200);
  // Stop the RESET pulse
//  RSTB = 1;
  CONTROL_PORT |= (1<<RSTB);   // RSTB = 1
}

// Turns the display (both left and right side) ON
void DisplayOn()
{
  DisplayWrite(LEFT, 0b00111111, CONTROL);
  DisplayWrite(RIGHT, 0b00111111, CONTROL);
}

// Turns the display (both left and right side) OFF
void DisplayOff()
{
  DisplayWrite(LEFT, 0b00111110, CONTROL);
  DisplayWrite(RIGHT, 0b00111110, CONTROL);
}

// Clears all pixels at the whole screen (left and right)
void ClearScreen()
{
  ClearHalfScreen(LEFT);
  ClearHalfScreen(RIGHT);
}

// Displays a graphical image (whole screen)
// The parameter is a pointer to the bit array defining the image
void DisplayPic(const char *picArray)
{
unsigned char i, j;

  for (i=0; i<8; i++)
  {
    for (j= 0; j<128; j++)
    {
      if (j == 0)
      {
        SetPage(LEFT,i);
        SetY(LEFT,0);
      }
      else if (j == 64)
      {
        SetPage(RIGHT,i);
        SetY(RIGHT,0);
      }
      if (j < 64)
        DisplayWrite(LEFT, *picArray++, DATA);
      else   
        DisplayWrite(RIGHT,*picArray++, DATA);
    }    
  }
}

// Sets one pixel at x,y
// Notice: x = Horizontal (0-127), y = Vertical (0-63)
// This corresponds to the "logical" x and y terms
// in contrast to the display internal definitions
void SetPixel(unsigned char x, unsigned char y)
{
unsigned char bit_no;
unsigned char tmp;

  if (( x < 128) && (y < 64))
  {
    bit_no = 7-(y%8);
    // Left half 
    if (x < 64)
    {
      //SetY(LEFT, x);
      SetPage(LEFT, 7-(y/8));
      SetY(LEFT, x);
      // Dummy read
      DisplayRead(LEFT, DATA);
      // - followed by actual read
      tmp = DisplayRead(LEFT, DATA);      
      SetY(LEFT, x);
      DisplayWrite(LEFT, ((1<<bit_no) | tmp), DATA);
    }  
    else
    // Right half
    {
      //SetY(RIGHT, x-64);
      SetPage(RIGHT, 7-(y/8));   
      SetY(RIGHT, x-64);
      // Dummy read
      DisplayRead(RIGHT, DATA);
      // - followed by actual read      
      tmp = DisplayRead(RIGHT, DATA);      
      SetY(RIGHT, x-64);
      DisplayWrite(RIGHT, ((1<<bit_no) | tmp), DATA);
    }
  }  
}

// Draws one horizontal line
// "StartX, StartY" is the (logical) start position of the line
// "Length" is the line length in pixels
void Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length)
{
unsigned char x;

  for (x=StartX; x<(StartX+Length); x++)
    SetPixel(x,StartY);
}
