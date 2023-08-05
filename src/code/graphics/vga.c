#include <string.h>
#include <vga.h>

volatile char* VGAMEM = (volatile char*)0xB8000;

char vga_createColor(char foreground, char background) {return foreground | background << 4;}

void vga_printc(char c, char color, int x, int y){
	int offset = (y*2) * 80 + (x*2);
	
	VGAMEM[offset] = c;
	VGAMEM[offset+1] = color;

	return;
}

void vga_print(char* string, char color, int x, int y){
	for(int i = 0; string[i] != '\0'; i++){
		if(x == 80){
			x = 0;
			y++;

			if(y == 25){
				return;
			}
		}

		vga_printc(string[i], color, x, y);
		x++;
	}
	
	return;
}

void vga_printi(int number, char color, int x, int y){
	char string[11];
	itoa(number, string, 10);
	vga_print(string, color, x, y);

	return;
}