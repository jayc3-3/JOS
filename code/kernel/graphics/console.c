#include <bool.h>
#include <multiboot.h>
#include <console.h>
#include <graphics.h>
#include <string.h>

bool console_active = false;
unsigned char console_cursorx;
unsigned char console_cursory;

unsigned char console_width;
unsigned char console_height;
int console_scale = 2;

int console_text;
int console_normal;
int console_info;
int console_warning;
int console_error;
int console_background;

double floor(double number){
	if(number != number){
		return number;
	}

	long long newNumber = (long long)number;
	double dNumber = (double)newNumber;

	if(dNumber == number || number >= 0)
		return dNumber;
	else
		return dNumber - 1;
}

bool console_init(multiboot_info_t* multiboot_info, int text_color, int info_color, int warning_color, int error_color, int background_color, bool active){
	if(!graphics_init(multiboot_info))
		return false;
	
	console_width = (int)floor((double)multiboot_info->framebuffer_width / 16.0) - 1;
	console_height = (int)floor((double)multiboot_info->framebuffer_height / 16.0) - 1;
	console_normal = text_color;
	console_info = info_color;
	console_warning = warning_color;
	console_error = error_color;
	console_background = background_color;
	
	console_text = console_normal;
	
	console_active = active;
	if(console_active){
		if(!console_clear())
			return false;
		
		if(!console_printi("Console successfully initialized\n"))
			return false;
		if(!console_printi("Console width: "))
			return false;
		if(!console_printint(console_width))
			return false;
		if(!console_printi("Console height: "))
			return false;
		if(!console_printint(console_height))
			return false;
		if(!console_printi("Console text color: "))
			return false;
		if(!console_printhex(console_normal))
			return false;
		if(!console_printi("Console info color: "))
			return false;
		if(!console_printhex(console_info))
			return false;
		if(!console_printi("Console warning color: "))
			return false;
		if(!console_printhex(console_warning))
			return false;
		if(!console_printi("Console error color: "))
			return false;
		if(!console_printhex(console_error))
			return false;
		if(!console_printi("Console background color: "))
			return false;
		if(!console_printhex(console_background))
			return false;
		
		return true;
	}
	
	return true;
}

bool console_printc(char c){
	if(!console_active)
		return false;
	
	switch(c){
		case '\n':
			console_cursorx = 1;
			console_cursory++;
			
			if(console_cursory > console_height){
				console_clear();
				return false;
			}
			return true;
		
		case '\r':
			console_cursorx = 1;
			
			return true;
		
		case '\b':
			if(console_cursorx == 1){
				if(console_cursory < 10)
					goto skip;
				
				console_cursorx = console_width+1;
				console_cursory--;
			}
			skip:
			console_cursorx--;
			graphics_rect(console_cursorx*16, console_cursory*17, 16, 16, console_background);
			
			return true;
		
		case '\t':
			for(int i = 0; i < 3; i++)
				console_printc(' ');
		
		default: break;
	}
	
	if(console_cursorx > console_width && console_cursory < console_height){
		console_cursorx = 1;
		console_cursory++;
	}
	
	if(console_cursory > console_height)
		return false;
	
	graphics_rect(console_cursorx*16, console_cursory*17, 16, 16, console_background);
	graphics_putc(c, console_cursorx*16, console_cursory*17, console_scale, console_text);
	console_cursorx++;
	
	return true;
}

bool console_clear(void){
	if(!console_active)
		return false;
	
	graphics_clear(console_background);
	console_cursorx = 1;
	console_cursory = 1;
	
	if(!console_print("       __ ____  _____\n"))
		return false;
	if(!console_print("      / // __ \\/ ___/\n"))
		return false;
	if(!console_print(" __  / // / / /\\__ \\ \n"))
		return false;
	if(!console_print("/ /_/ // /_/ /___/ / \n"))
		return false;
	if(!console_print("\\____/ \\____/ \\___/  \n"))
		return false;
	if(!console_print("\nVersion 0.0.2\n"))
		return false;
	
	for(int i = 0; i < console_width-1; i++)
		if(!console_printc('-'))
			return false;
	if(!console_printc('\n'))
		return false;
	
	return true;
}

bool console_print(char* string){
	if(!console_active)
		return false;
	
	console_text = console_normal;
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	return true;
}

bool console_printi(char* string){
	if(!console_active)
		return false;
	
	console_text = console_info;
	
	char* info = "INFO: ";
	
	for(int i = 0; info[i] != '\0'; i++)
		if(!console_printc(info[i]))
			return false;
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	return true;
}

bool console_printw(char* string){
	if(!console_active)
		return false;
	
	console_text = console_warning;
	
	char* warning = "WARNING: ";
	
	for(int i = 0; warning[i] != '\0'; i++)
		if(!console_printc(warning[i]))
			return false;
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	return true;
}

bool console_printe(char* string){
	if(!console_active)
		return false;
	
	console_text = console_error;
	
	char* error = "ERROR: ";
	
	for(int i = 0; error[i] != '\0'; i++)
		if(!console_printc(error[i]))
			return false;
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	return true;
}

bool console_printbin(int number){
	if(!console_active)
		return false;
	
	char string[33];
	
	string_itoa(number, string, 2);
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	if(!console_printc('\n'))
		return false;
	
	return true;
}

bool console_printint(int number){
	if(!console_active)
		return false;
	
	char string[12];
	
	string_itoa(number, string, 10);
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	if(!console_printc('\n'))
		return false;
	
	return true;
}

bool console_printhex(int number){
	if(!console_active)
		return false;
	
	char string[11];
	
	string_itoa(number, string, 16);
	
	for(int i = 0; string[i] != '\0'; i++)
		if(!console_printc(string[i]))
			return false;
	
	if(!console_printc('\n'))
		return false;
	
	return true;
}