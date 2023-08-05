#ifndef _CONSOLE_H
#define _CONSOLE_H

extern int cHeight;

void console_init(int framebufferWidth, int framebufferHeight, int textScale, int textColor, int backgroundColor);
void console_clear(void);
void console_gotoLine(int line);

int console_printc(char c);
void console_print(char* string);
void console_printi(int number);
void console_printh(int number);

#endif