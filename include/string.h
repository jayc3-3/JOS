#ifndef _STRING_H
#define _STRING_H

void string_reverse(char* string, int length);
int string_compare(char* string1, char* string2);
int string_length(char* string);

char* string_itoa(int number, char* string, int base);

#endif