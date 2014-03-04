/*
 * DisplayWrapper.c
 *
 * Created: 03-03-2014 17:04:07
 *  Author: Christian Svejstrup
 */ 

#include "DisplayWrapper.h"

void MatchCharacters(char character);

int isDispInit = 0;

void WriteToDisplay(char* dispStr)
{
	if (!isDispInit)
	{
		DisplayInit();
		DisplayOn();
		ClearScreen();
		isDispInit = 1;
	}
	
	while(*dispStr != '\0')
	{
		MatchCharacters(*dispStr);		
		dispStr++;
	}
	
	//if (*--dispStr != '\n')
	//{
		//MatchCharacters(' ');
	//}	
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
	
	switch (character)
	{
	case '1':
		SetNextCharAuto(one);
		break;
	case '2':
		SetNextCharAuto(two);
		break;
	case '3':
		SetNextCharAuto(three);
		break;
	case '4':
		SetNextCharAuto(four);
		break;
	case '5':
		SetNextCharAuto(five);
		break;
	case '6':
		SetNextCharAuto(six);
		break;
	case '7':
		SetNextCharAuto(seven);
		break;
	case '8':
		SetNextCharAuto(eight);
		break;
	case '9':
		SetNextCharAuto(nine);
		break;
	case '0':
		SetNextCharAuto(zero);
		break;	
	case 'T':
	case 't':
		SetNextCharAuto(T);
		break;
	case 'E':
	case 'e':
		SetNextCharAuto(E);
		break;
	case 'M':
		SetNextCharAuto(M);
		break;
	case 'm':
		SetNextCharAuto(m);
		break;
	case 'P':
	case 'p':
		SetNextCharAuto(P);
		break;
	case 'O':
	case 'o':
		SetNextCharAuto(O);
		break;
	case 'S':
	case 's':
		SetNextCharAuto(S);
		break;
	case 'A':	
		SetNextCharAuto(A);
		break;
	case 'a':
		SetNextCharAuto(a);
		break;
	case 'h':
		SetNextCharAuto(h);
		break;
	case 'L':
	case 'l':
		SetNextCharAuto(L);
		break;
	case 'R':
	case 'r':
		SetNextCharAuto(R);
		break;
	case ' ':
		SetNextCharAuto(space);
		break;
	case ':':
		SetNextCharAuto(colon);
		break;
	case '?':
		SetNextCharAuto(question);
		break;
	case '*':
		SetNextCharAuto(degree);
		break;
	case '\n':
		NextLine();
		break;
	case '\r':
		SetPosition(0);
		break;
	default:
		SetNextCharAuto(question);
	}	
}

void NewLine()
{
	NextLine();
}

void SetLine(int line)
{
	SetLineNum(line);
}

void SetPosition(int pos)
{
	SetPositionNum(pos);
}
