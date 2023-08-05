#include <string.h>

void str_reverse(char* string, int length){
	int start = 0;
	int end = length - 1;

	while(start < end){
		char tempChar = string[start];
		string[start] = string[end];
		string[end] = tempChar;
		end--;
		start++;
	}

	return;
}

char* itoa(int number, char* string, int base){
	int i = 0;
	int negative = 0;

	if(number == 0){
		string[i++] = '0';
		string[i] = '\0';
		
		return string;
	}

	if(number < 0 && base == 10){
		negative = 1;
		number = -number;
	}

	while(number != 0){
		int remainder = number % base;
		string[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		number /= base;
	}

	if(negative)
		string[i++] = '-';
	
	string[i] = '\0';

	str_reverse(string, i);

	return string;
}