#include <ps2.h>
#include <console.h>
#include <ports.h>
#include <ps2Keyboard.h>

int capital = 0;

unsigned char US_ENG_KEYBOARD[] = {
	0x00,
	0x00,
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'\b',
	0x00,
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n',
	0x00,
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'`',
	0x00,
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	0x00,
	'*',
	0x00,
	' ',
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	'7',
	'8',
	'9',
	'-',
	'4',
	'5',
	'6',
	'+',
	'1',
	'2',
	'3',
	'0',
	'.',
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};

unsigned char US_ENG_KEYBOARD_CAP[] = {
	0x00,
	0x00,
	'!',
	'@',
	'#',
	'$',
	'%',
	'^',
	'&',
	'*',
	'(',
	')',
	'_',
	'+',
	'\b',
	0x00,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'{',
	'}',
	'\n',
	0x00,
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	':',
	'"',
	'~',
	0x00,
	'|',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	'<',
	'>',
	'?',
	0x00,
	'*',
	0x00,
	' ',
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	'7',
	'8',
	'9',
	'-',
	'4',
	'5',
	'6',
	'+',
	'1',
	'2',
	'3',
	'0',
	'.',
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};

void ps2Keyboard_init(void){
	ps2_sendPort(PS2_COMMAND, 0xAE);

	start:
	ps2_sendPort(PS2_DATA, 0xFF);
	switch(ps2_readPort(PS2_DATA)){
		case 0xFE:
			goto start;
		
		case 0xFC:
			console_print("ERROR: Unable to initialize PS/2 keyboard\n");
			ps2_sendPort(PS2_COMMAND, 0xAD);
			return;

		case 0xFD:
			console_print("ERROR: Unable to initialize PS/2 keyboard\n");
			ps2_sendPort(PS2_COMMAND, 0xAD);
			return;
		
		case 0xAA: break;
		default: break;
	}
	
	ps2_sendPort(PS2_DATA, 0xF0);
	ps2_sendPort(PS2_DATA, 0x01);

	console_print("INFO: Successfully initialized keyboard\n");

	return;
}

unsigned char ps2Keyboard_pollInput(void){
	unsigned char input = ps2_readPort(PS2_DATA);
	if(input > 0x58)
		return 0x00;
	
	return input;
}

void ps2Keyboard_printInput(unsigned char keyboardChar){
	if(keyboardChar == 0x2A)
		capital = 1 - capital;

	if(keyboardChar > 0x58)
		return;
	if(keyboardChar > sizeof(US_ENG_KEYBOARD))
		return;
	
	if(!capital)
		console_printc(US_ENG_KEYBOARD[(int)keyboardChar]);
	else
		console_printc(US_ENG_KEYBOARD_CAP[(int)keyboardChar]);

	return;
}