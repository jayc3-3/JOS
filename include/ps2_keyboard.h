#ifndef _PS2_KEYBOARD_H
#define _PS2_KEYBOARD_H

#define PS2_KEYBOARD_SHORT   1
#define PS2_KEYBOARD_NCD_N97 2
#define PS2_KEYBOARD_122_KEY 3
#define PS2_KEYBOARD_NCD_SUN 4
#define PS2_KEYBOARD_MF2     5
#define PS2_KEYBOARD_UNKNOWN 6

#define PS2_KEYBOARD_A 0x1E
#define PS2_KEYBOARD_B 0x30
#define PS2_KEYBOARD_C 0x2E
#define PS2_KEYBOARD_D 0x20
#define PS2_KEYBOARD_E 0x12

extern int ps2_keyboard_type;
extern unsigned char ps2_keyboard_pressed;
extern unsigned char ps2_keyboard_released;
extern bool ps2_keyboard_key_pressed;

bool ps2_keyboard_init(void);
void ps2_keyboard_disable_interrupts(void);
void ps2_keyboard_enable_interrupts(void);

char ps2_keyboard_translate(char input);

#endif