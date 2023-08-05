#ifndef _VGA_H
#define _VGA_H

char vga_createColor(char foreground, char background);

void vga_print(char* string, char color, int x, int y);
void vga_printi(int number, char color, int x, int y);

#endif