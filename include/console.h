#ifndef _CONSOLE_H
#define _CONSOLE_H

extern bool console_active;
bool console_init(multiboot_info_t* multiboot_info, int text_color, int info_color, int warning_color, int error_color, int background_color, bool active);

bool console_clear(void);
bool console_printc(char c);
bool console_print(char* string);

bool console_printi(char* string);
bool console_printw(char* string);
bool console_printe(char* string);

bool console_printbin(int number);
bool console_printint(int number);
bool console_printhex(int number);

#endif