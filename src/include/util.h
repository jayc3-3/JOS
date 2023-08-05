#ifndef _UTIL_H
#define _UTIL_H

#define CHECK_BIT(variable, position) ((variable) & (1 << (position)))

void mem_copy(char* src, char* dst, int bytes);

#endif