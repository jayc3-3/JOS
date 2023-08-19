#include <bool.h>
#include <ps2_keyboard.h>
#include <ps2.h>
#include <pic.h>
#include <util.h>
#include <multiboot.h>
#include <console.h>
#include <interrupts.h>
#include <cpu.h>

int ps2_keyboard_port;
int ps2_keyboard_type;

unsigned char ps2_keyboard_pressed;
unsigned char ps2_keyboard_released;
bool ps2_keyboard_capital = false;
bool ps2_keyboard_ignore_next = false;

bool ps2_keyboard_key_pressed = false;

void ps2_keyboard_handler(struct registers* regs){
	unsigned char input = cpu_byte_in(0x60);
	
	if(ps2_keyboard_ignore_next){
		ps2_keyboard_ignore_next = false;
		return;
	}
	
	if(input == 0xE0){
		ps2_keyboard_ignore_next = true;
		return;
	}
	
	if(input < 0x59){
		ps2_keyboard_pressed = input;
		ps2_keyboard_key_pressed = true;
		
		if(input == 0x2A) ps2_keyboard_capital = 1 - ps2_keyboard_capital;
	}
	else if(input < 0xD9)
		ps2_keyboard_released = input;
	
	return;
}

bool ps2_keyboard_init(void){
	if(!ps2)
		return false;
	
	if(!ps2_port1)
		goto ps2_keyboard_init_test_port2;
	
	ps2_byte_out(PS2_DAT, 0xF2);
	ps2_byte_in(PS2_DAT);
	
	get_response1:
	unsigned char response1 = ps2_byte_in(PS2_DAT);
	if(response1 == 0xFA)
		goto get_response1;
	
	if(response1 != 0xAB && response1 != 0xAC)
		goto ps2_keyboard_init_test_port2;
	
	unsigned char response2 = ps2_byte_in(PS2_DAT);
	
	ps2_keyboard_port = 1;
	
	switch(response2){
		case 0x83:
			ps2_keyboard_type = PS2_KEYBOARD_MF2;
			break;
		
		case 0x41:
			ps2_keyboard_type = PS2_KEYBOARD_MF2;
			break;
		
		case 0xC1:
			ps2_keyboard_type = PS2_KEYBOARD_MF2;
			break;
		
		case 0x84:
			ps2_keyboard_type = PS2_KEYBOARD_SHORT;
			break;
		
		case 0x85:
			ps2_keyboard_type = PS2_KEYBOARD_NCD_N97;
			break;
		
		case 0x86:
			ps2_keyboard_type = PS2_KEYBOARD_122_KEY;
			break;
		
		case 0xA1:
			ps2_keyboard_type = PS2_KEYBOARD_NCD_SUN;
			break;
		
		default:
			ps2_keyboard_type = PS2_KEYBOARD_UNKNOWN;
	}
	
	console_printi("PS/2 keyboard found on PS/2 port 1\n");
	
	goto done;
	
	ps2_keyboard_init_test_port2:
	if(!ps2_port2){
		console_printw("No PS/2 keyboard found\n");
		return false;
	}
	
	ps2_byte_out(PS2_COM, 0xD4);
	ps2_byte_out(PS2_DAT, 0xF2);
	ps2_byte_in(PS2_DAT);
	
	get_response3:
	unsigned char response3 = ps2_byte_in(PS2_DAT);
	if(response3 == 0xFA)
		goto get_response3;
	
	if(response3 != 0xAB && response3 != 0xAC){
		console_printw("No PS/2 keyboard found\n");
		return false;
	}
	
	unsigned char response4 = ps2_byte_in(PS2_DAT);
	
	ps2_keyboard_port = 2;
	
	switch(response4){
		case 0x83:
			ps2_keyboard_type = PS2_KEYBOARD_MF2;
			break;
		
		case 0xC1:
			ps2_keyboard_type = PS2_KEYBOARD_MF2;
			break;
		
		case 0x84:
			ps2_keyboard_type = PS2_KEYBOARD_SHORT;
			break;
		
		case 0x85:
			ps2_keyboard_type = PS2_KEYBOARD_NCD_N97;
			break;
		
		case 0x86:
			ps2_keyboard_type = PS2_KEYBOARD_122_KEY;
			break;
		
		case 0xA1:
			ps2_keyboard_type = PS2_KEYBOARD_NCD_SUN;
			break;
		
		default:
			ps2_keyboard_type = PS2_KEYBOARD_UNKNOWN;
	}
	
	console_printi("Keyboard found on PS/2 port 2\n");
	
	goto done;
	
	done:
	
	set_scancode:
	if(ps2_keyboard_port == 2)
		ps2_byte_out(PS2_DAT, 0xD4);
	ps2_byte_out(PS2_DAT, 0xF0);
	ps2_byte_out(PS2_DAT, 0x01);
	switch(ps2_byte_in(PS2_DAT)){
		case 0xFA:
			break;
		
		case 0xFE:
			goto set_scancode;
		
		default: goto set_scancode;
	}
	
	isr_install(33, ps2_keyboard_handler);
	
	console_printi("Successfully initialized PS/2 keyboard\n");
	
	switch(ps2_keyboard_type){
		case PS2_KEYBOARD_SHORT:
			console_printi("Keyboard type: SHORT\n");
			break;
		
		case PS2_KEYBOARD_NCD_N97:
			console_printi("Keyboard type: NCD-97\n");
			break;
		
		case PS2_KEYBOARD_122_KEY:
			console_printi("Keyboard type: 122-Key\n");
			break;
		
		case PS2_KEYBOARD_NCD_SUN:
			console_printi("Keyboard type: NCD Sun\n");
			break;
		
		case PS2_KEYBOARD_MF2:
			console_printi("Keyboard type: MF2\n");
			break;
		
		case PS2_KEYBOARD_UNKNOWN:
			console_printi("Keyboard type: Unknown\n");
			break;
	}
	
	return true;
}

void ps2_keyboard_enable_interrupts(void){
	if(ps2_keyboard_port == 1){
		ps2_byte_out(PS2_COM, 0x20);
		unsigned char config_byte = ps2_byte_in(PS2_DAT);
		config_byte |= 1 << 0;
		ps2_byte_out(PS2_COM, 0x60);
		ps2_byte_out(PS2_DAT, config_byte);
		
		ps2_keyboard_enable_interrupts_port1:
		ps2_byte_out(PS2_DAT, 0xF4);
		switch(ps2_byte_in(PS2_DAT)){
			case 0xFA:
				break;
			
			default:
				goto ps2_keyboard_enable_interrupts_port1;
		}
	}
	else if(ps2_keyboard_port == 2){
		ps2_byte_out(PS2_COM, 0x20);
		unsigned char config_byte = ps2_byte_in(PS2_DAT);
		config_byte |= 1 << 1;
		ps2_byte_out(PS2_COM, 0x60);
		ps2_byte_out(PS2_DAT, config_byte);
		
		ps2_keyboard_enable_interrupts_port2:
		ps2_byte_out(PS2_COM, 0xD4);
		ps2_byte_out(PS2_DAT, 0xF4);
		switch(ps2_byte_in(PS2_DAT)){
			case 0xFA:
				break;
			
			default:
				goto ps2_keyboard_enable_interrupts_port2;
		}
	}
	
	pic_clear_mask(1);
	
	return;
}

void ps2_keyboard_disable_interrupts(void){
	if(ps2_keyboard_port == 1){
		ps2_byte_out(PS2_COM, 0x20);
		unsigned char config_byte = ps2_byte_in(PS2_DAT);
		config_byte &= ~(1 << 1);
		ps2_byte_out(PS2_COM, 0x60);
		ps2_byte_out(PS2_DAT, config_byte);
		
		ps2_keyboard_disable_interrupts_port1:
		ps2_byte_out(PS2_DAT, 0xF5);
		switch(ps2_byte_in(PS2_DAT)){
			case 0xFA:
				break;
			
			default:
				goto ps2_keyboard_disable_interrupts_port1;
		}
	}
	else if(ps2_keyboard_port == 2){
		ps2_byte_out(PS2_COM, 0x20);
		unsigned char config_byte = ps2_byte_in(PS2_DAT);
		config_byte &= ~(1 << 1);
		ps2_byte_out(PS2_COM, 0x60);
		ps2_byte_out(PS2_DAT, config_byte);
		
		ps2_keyboard_disable_interrupts_port2:
		ps2_byte_out(PS2_COM, 0xD4);
		ps2_byte_out(PS2_DAT, 0xF5);
		switch(ps2_byte_in(PS2_DAT)){
			case 0xFA:
				break;
			
			default:
				goto ps2_keyboard_disable_interrupts_port2;
		}
	}
	
	pic_set_mask(1);
	
	return;
}

char PS2_KEYBOARD_QWERTY_US[] = {
	0x00, 0x00,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0x00,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0x00,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
	0x00, '*',
	0x00, ' ',
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	'7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
	0x00, 0x00, 0x00, 0x00, 0x00
};

char PS2_KEYBOARD_QWERTY_US_CAP[] = {
	0x00, 0x00,
	'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0x00,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
	0x00,
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
	0x00, '*',
	0x00, ' ',
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	'7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
	0x00, 0x00, 0x00, 0x00, 0x00
};

char ps2_keyboard_translate(char input){
	char translated;
	
	if(ps2_keyboard_capital)
		translated = PS2_KEYBOARD_QWERTY_US_CAP[input];
	else
		translated = PS2_KEYBOARD_QWERTY_US[input];
	
	return translated;
}