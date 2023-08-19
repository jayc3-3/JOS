#include <string.h>
#include <bool.h>

void string_reverse(char* string, int length){
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

int string_compare(char* string1, char* string2){
	for(int i = 0; string1[i] != '\0'; i++){
		if(string1[i] != string2[i])
			return false;
	}
	
	return true;
}

int string_length(char* string){
	int length = 0;
	
	for(int i = 0; string[i] != '\0'; i++){
		length++;
	}
	
	return length;
}

char* string_itoa(int number, char* string, int base){
	int i = 0;
	bool negative = false;
	
	if(number == 0){
		if(base == 2){
			string[i++] = '0';
			string[i++] = 'b';
			string[i++] = '0';
			string[i] = '\0';
		}
		else if(base == 16){
			string[i++] = '0';
			string[i++] = 'x';
			string[i++] = '0';
			string[i] = '\0';
		}
		else{
			string[i++] = '0';
			string[i] = '\0';
		}
		string_reverse(string, i);
		
		return string;
	}
	
	if(number < 0 && base == 10){
		negative = true;
		number = -number;
	}
	
	while(number != 0){
		int remainder = number % base;
		string[i++] = (remainder > 9)? (remainder - 10) + 'a' : remainder + '0';
		number /= base;
	}
	
	if(negative) string[i++] = '-';
	
	if(base == 2){
		string[i++] = 'b';
		string[i++] = '0';
	}
	else if(base == 16){
		string[i++] = 'x';
		string[i++] = '0';
	}
	
	string[i] = '\0';
	string_reverse(string, i);
	
	return string;
}