/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
*/

#include<stdio.h>

int findSingleOccurenceNumber(int *A, int len) {

	if(A == NULL || len < 1)
		return -1;

	int one = 0;
	int twos = 0;
 
    int commonBitMask;
 
    for(int i = 0; i < len; ++i){
		twos  = twos | (one & A[i]);
		one  = one ^ A[i];
		commonBitMask = ~(one & twos);
		one &= commonBitMask;
		twos &= commonBitMask;
	}
	
    return one;
}