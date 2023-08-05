#include <framebuffer.h>
#include <string.h>
#include <math.h>
#include <console.h>

int cursorX;
int cursorY;
int cWidth;
int cHeight;
int cTextColor;
int cBackColor;

void console_init(int framebufferWidth, int framebufferHeight, int textColor, int backgroundColor){
	cWidth = (int)math_floor((double)framebufferWidth / 16.0) - 1;
	cHeight = (int)math_floor((double)framebufferHeight / 16.0) - 1;
	cTextColor = textColor;
	cBackColor = backgroundColor;

	console_clear();
	console_print("       ______  _____\n");
	console_print("      / / __ \\/ ___/\n");
	console_print(" __  / / / / /\\__ \\ \n");
	console_print("/ /_/ / /_/ /___/ /\n");
	console_print("\\____/\\____//____/\n");

	for(int i = 0; i < cWidth-1; i++){
		console_printc('-');
	}
	console_printc('\n');

	console_print("Version 0.0.1\n\n");
	console_print("INFO: Successfully initialized console\n");
	console_print("INFO: Console width: ");
	console_printi(cWidth);
	console_print("INFO: Console height: ");
	console_printi(cHeight);

	return;
}

void console_clear(void){
	fb_clearScreen(cBackColor);
	cursorX = 1;
	cursorY = 1;

	return;
}

void console_gotoLine(int line){
	if(line > cHeight)
		return;
	
	cursorX = 1;
	cursorY = line;

	return;
}

int console_printc(char c){
	switch(c){
		case '\n':
			cursorX = 1;
			cursorY++;

			if(cursorY > cHeight)
				return 0;
			
			return 1;
		
		case '\r':
			cursorX = 1;
		
		default: break;
	}

	if(cursorX > cWidth || cursorY > cHeight)
		return 0;

	fb_drawRect(cursorX*16, cursorY*16, 16, 16, cBackColor);
	fb_drawChar(c, cursorX*16, cursorY*16, cTextColor);
	cursorX++;

	if(cursorX > cWidth && cursorY < cHeight)
		cursorY++;

	return 1; 
}

void console_print(char* string){
	for(int i = 0; string[i] != '\0'; i++){
		if(!console_printc(string[i])){
			console_clear();
			return;
		}
	}

	return;
}

void console_printi(int number){
	char string[12];
	itoa(number, string, 10);
	console_print(string);
	console_printc('\n');

	return;
}

void console_printh(int number){
	char string[12];
	itoa(number, string, 16);
	console_print(string);
	console_printc('\n');

	return;
}