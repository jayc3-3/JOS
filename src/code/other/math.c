#include <math.h>

double math_floor(double number){
	if(number != number){
		return number;
	}

	long long newNumber = (long long)number;
	double dNumber = (double)newNumber;

	if(dNumber == number || number >= 0)
		return dNumber;
	else
		return dNumber - 1;
}

int math_ceiling(float number){
	int iNumber = (int)number;
	if(number == (float)iNumber)
		return iNumber;
	else
		return iNumber + 1;
}