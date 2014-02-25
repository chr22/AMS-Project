
/*
  PRELIMINARY TEST PROGRAM FOR DM128064A Graphic Display Module
  AVR GCC version
  
  Henning Hargaard February 5, 2014. 
  
*/

// Max crystal frequency = 16 MHz => T = 62 ns

#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>
#include "Drivers/DEM128064A.h"

//const char capitalletters[] = {
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0xE0, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40,
//0x00, 0x00, 0x00, 0x00, 0xE0, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x20,
//0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00,
//0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00,
//0xE0, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
//0x00, 0x00, 0xE0, 0x00, 0x00, 0x80, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x06, 0x05, 0x04, 0x05, 0x06, 0x18, 0x00, 0x00, 0x00, 0x00,
//0x1F, 0x11, 0x11, 0x11, 0x11, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x08,
//0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x11,
//0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x07, 0x08, 0x10, 0x10, 0x12, 0x0A, 0x06, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x01, 0x01, 0x01, 0x01,
//0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x0F, 0x00, 0x00,
//0x00, 0x00, 0x1F, 0x02, 0x01, 0x03, 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10,
//0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x30, 0xC0, 0x00, 0xC0, 0x30, 0xF8, 0x00, 0x00, 0x00, 0x00,
//0xF8, 0x10, 0x60, 0x80, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x10, 0x08, 0x08, 0x08, 0x10,
//0xE0, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x10,
//0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x48, 0x48, 0xC8, 0x48, 0x30, 0x00,
//0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x88, 0x88, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xF8,
//0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00,
//0x18, 0x60, 0x80, 0x00, 0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x18, 0xE0, 0x00, 0x80, 0x70, 0x08,
//0x70, 0x80, 0x00, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x01, 0x06, 0x01, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
//0x07, 0x00, 0x00, 0x01, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04, 0x02,
//0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
//0x04, 0x05, 0x05, 0x06, 0x05, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00,
//0x00, 0x00, 0x00, 0x02, 0x04, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x01, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x01, 0x00, 0x00,
//0x00, 0x01, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xCC, 0x30, 0x30, 0xCC, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02,
//0x0C, 0x10, 0xE0, 0x10, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x62, 0x1A, 0x06, 0x02,
//0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x82, 0x42,
//0x22, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x84, 0x02, 0x12, 0x12, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x60,
//0x58, 0x44, 0xFE, 0x40, 0x00, 0x00, 0x00, 0x00, 0x98, 0x16, 0x12, 0x12, 0xE2, 0x00, 0x00, 0x00,
//0x00, 0xFC, 0x12, 0x12, 0x12, 0xE4, 0x00, 0x00, 0x00, 0x00, 0x02, 0xC2, 0x32, 0x0E, 0x02, 0x00,
//0x00, 0x00, 0x00, 0xEC, 0x12, 0x12, 0x12, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x22, 0x22, 0x22,
//0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x80, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00,
//0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01,
//0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x01, 0x01,
//0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x00, 0x01, 0x01, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x81, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x01, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00,
//0x80, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x5F, 0x00,
//0x00, 0x00, 0x00, 0x7C, 0x83, 0x39, 0x44, 0x42, 0x22, 0x7C, 0x46, 0x21, 0x9E, 0x00, 0x00, 0x00,
//0x00, 0x72, 0x1E, 0x73, 0x1E, 0x13, 0x00, 0x00, 0x00, 0x00, 0x23, 0x44, 0xFF, 0x44, 0x39, 0x00,
//0x00, 0x00, 0x00, 0x03, 0x04, 0x44, 0x33, 0x0C, 0x33, 0x48, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00,
//0x04, 0x03, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00, 0x30, 0x4B, 0x44, 0x4C, 0x33, 0x50, 0x00, 0x00,
//0x00, 0x00, 0x05, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
//0x3E, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
//0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};

const char clear[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char two[] = {
	0b01111001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001111, 0b00000000
};

const char one[] = {
	0b01000001, 0b01000001,	0b01000001, 0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b00000000
};

const char onetwo[] = {
	0b01000001, 0b01000001,	0b01000001, 0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b00000000,
	0b01111001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001111, 0b00000000,
	0b01000001, 0b01000001,	0b01000001, 0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b00000000,
	0b01111001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001111, 0b00000000
};

int main()
{
  DisplayInit();
  DisplayOn();
  ClearScreen();

  char dest[16];
  //memcpy(dest, )
  //strncat(one, two, 1);
  
  strcpy(dest, one);
  //strcat(dest, two);
  
  //clears screen
  DisplayPic(clear);
  
  DisplayCharArray(onetwo);
    
  while(1)
  {}
}