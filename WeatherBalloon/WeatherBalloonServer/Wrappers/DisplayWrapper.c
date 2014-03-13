/*
 * DisplayWrapper.c
 *
 * Created: 03-03-2014 17:04:07
 *  Author: Christian Svejstrup
 */ 

#include "DisplayWrapper.h"

void MatchCharacters(char character);

int isDispInit = 0;

void DisplayWrapper_Ctor()
{
	DEM128064A_DisplayInit();
	DEM128064A_DisplayOn();
	DEM128064A_ClearScreen();
	isDispInit = 1;
}

void DisplayWrapper_WriteToDisplay(char* dispStr)
{
	if (!isDispInit)
	{
		DisplayWrapper_Ctor();
	}
	
	while(*dispStr != '\0')
	{
		MatchCharacters(*dispStr);		
		dispStr++;
	}
}

void MatchCharacters(char character)
{
	const char zero[] = {
		0b01111111, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01111111, 0b00000000
	};

	const char one[] = {
		0b01000001, 0b01000001,	0b01000001, 0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b00000000
	};

	const char two[] = {
		0b01111001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001111, 0b00000000
	};

	const char three[] = {
		0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01111111, 0b00000000
	};

	const char four[] = {
		0b00001111, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b01111111, 0b00000000
	};

	const char five[] = {
		0b01001111, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01111001, 0b00000000
	};

	const char six[] = {
		0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01111001, 0b00000000
	};

	const char seven[] = {
		0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b01111111, 0b00000000
	};

	const char eight[] = {
		0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01111111, 0b00000000
	};

	const char nine[] = {
		0b01001111, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01111111, 0b00000000
	};

	const char space[] = {
		0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000
	};	
	
	const char point[] = {
		0b00000000, 0b00000000, 0b00000000, 0b01100000, 0b01100000, 0b00000000, 0b00000000, 0b00000000
	};
	
	const char T[] = {
		0b00000001, 0b00000001, 0b00000001, 0b01111111, 0b00000001, 0b00000001, 0b00000001, 0b00000000
	};
	
	const char E[] = {
		0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b00000000
	};
	
	const char M[] = {
		0b01111111, 0b00000010, 0b00000100, 0b00001000, 0b00000100, 0b00000010, 0b01111111, 0b00000000
	};
	
	const char m[] = {
		0b01110000, 0b00001000, 0b00010000, 0b00100000, 0b00010000, 0b00001000, 0b01110000, 0b00000000
	};
	
	const char P[] = {
		0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00001001, 0b00001001, 0b00000110, 0b00000000
	};
	
	const char O[] = {
		0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b00111110, 0b00000000
	};

	const char C[] = {
		0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b01000001, 0b00100010, 0b00000000
	};	
	
	const char R[] = {
		0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00011001, 0b00101001, 0b01000110, 0b00000000
	};
	
	const char S[] = {
		0b01000110, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b01001001, 0b00110001, 0b00000000
	};	
	
	const char A[] = {
		0b01100000, 0b00011000, 0b00010110, 0b00010001, 0b00010110, 0b00011000, 0b01100000, 0b00000000
	};
	
	const char a[] = {
		0b00100000, 0b01010100, 0b01010100, 0b01010100, 0b01010100, 0b01010100, 0b01111000, 0b00000000
	};
	
	const char h[] = {
		0b01111111, 0b00010000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b01110000, 0b00000000 
	};
	
	const char L[] = {
		0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b00000000
	};
	
	const char question[] = {
		0b00000110, 0b00000001, 0b00000001, 0b00000001, 0b01010001, 0b00001001, 0b00000110, 0b00000000
	};
	
	const char colon[] = {
		0b00000000, 0b00000000, 0b00100100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 
	};
	
	const char degree[] = {
		0b00000000, 0b00000111, 0b00000101, 0b00000111, 0b00000000, 0b00000000, 0b00000000, 0b00000000
	};
	
	const char delta[] = {
		0b01100000, 0b01011000, 0b01000110, 0b01000001, 0b01000111, 0b01011100, 0b01110000, 0b00000000
	};
	
	switch (character)
	{
	case '1':
		DEM128064A_SetNextCharAuto(one);
		break;
	case '2':
		DEM128064A_SetNextCharAuto(two);
		break;
	case '3':
		DEM128064A_SetNextCharAuto(three);
		break;
	case '4':
		DEM128064A_SetNextCharAuto(four);
		break;
	case '5':
		DEM128064A_SetNextCharAuto(five);
		break;
	case '6':
		DEM128064A_SetNextCharAuto(six);
		break;
	case '7':
		DEM128064A_SetNextCharAuto(seven);
		break;
	case '8':
		DEM128064A_SetNextCharAuto(eight);
		break;
	case '9':
		DEM128064A_SetNextCharAuto(nine);
		break;
	case '0':
		DEM128064A_SetNextCharAuto(zero);
		break;	
	case 'T':
	case 't':
		DEM128064A_SetNextCharAuto(T);
		break;
	case 'E':
	case 'e':
		DEM128064A_SetNextCharAuto(E);
		break;
	case 'M':
		DEM128064A_SetNextCharAuto(M);
		break;
	case 'm':
		DEM128064A_SetNextCharAuto(m);
		break;
	case 'P':
	case 'p':
		DEM128064A_SetNextCharAuto(P);
		break;
	case 'O':
	case 'o':
		DEM128064A_SetNextCharAuto(O);
		break;
	case 'C':
	case 'c':
		DEM128064A_SetNextCharAuto(C);
		break;
	case 'S':
	case 's':
		DEM128064A_SetNextCharAuto(S);
		break;
	case 'A':	
		DEM128064A_SetNextCharAuto(A);
		break;
	case 'a':
		DEM128064A_SetNextCharAuto(a);
		break;
	case 'h':
		DEM128064A_SetNextCharAuto(h);
		break;
	case 'L':
	case 'l':
		DEM128064A_SetNextCharAuto(L);
		break;
	case 'R':
	case 'r':
		DEM128064A_SetNextCharAuto(R);
		break;
	case ' ':
		DEM128064A_SetNextCharAuto(space);
		break;
	case ':':
		DEM128064A_SetNextCharAuto(colon);
		break;
	case '?':
		DEM128064A_SetNextCharAuto(question);
		break;
	case '*':
		DEM128064A_SetNextCharAuto(degree);
		break;
	case '.':
		DEM128064A_SetNextCharAuto(point);
		break;
	case 'd':
		DEM128064A_SetNextCharAuto(delta);
		break;
	case '\n':
		DEM128064A_NewLine();
		break;
	case '\r':
		DisplayWrapper_SetPosition(0);
		break;
	default:
		DEM128064A_SetNextCharAuto(question);
	}	
}

void DisplayWrapper_NewLine()
{
	DEM128064A_NewLine();
}

void DisplayWrapper_SetLine( int line )
{
	DEM128064A_SetLineNum(line);
}

void DisplayWrapper_SetPosition( int pos )
{
	DEM128064A_SetPositionNum(pos);
}

void DisplayWrapper_ClearScreen()
{
	if (!isDispInit)
	{
		DisplayWrapper_Ctor();
	}
	
	DEM128064A_ClearScreen();
	DEM128064A_SetPositionNum(0);
	DEM128064A_SetLineNum(0);
}