/*
 * DisplayWrapper.c
 *
 * Created: 03-03-2014 17:04:07
 *  Author: Christian Svejstrup
 */ 

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
		*dispStr++;
	}
	
	MatchCharacters(" ");
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
	case ' ':
		SetNextCharAuto(space);
		break;
	default:
		SetNextCharAuto(space);
	}
}
