#ifndef _PS2KEYBOARD_H
#define _PS2KEYBOARD_H

void ps2Keyboard_init(void);
unsigned char ps2Keyboard_pollInput(void);
void ps2Keyboard_printInput(unsigned char keyboardChar);

void ps2Keyboard_disable(void);
void ps2Keyboard_enable(void);

#endif