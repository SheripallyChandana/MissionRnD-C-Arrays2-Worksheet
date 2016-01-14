/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

void convertDateInCharsToIntegers2(char* dateInChars, int* date, int* month, int* year){

	int result = 0;
	bool hiphenCount = false;
	int index;

	for (index = 0; dateInChars[index] != '\0'; ++index){

		if (dateInChars[index] == '-'){
			if (hiphenCount == true){
				*month = result;
				result = 0;
			}
			else{
				*date = result;
				result = 0;
				hiphenCount = true;
			}
			continue;
		}

		result = result * 10 + dateInChars[index] - '0';
	}
	*year = result;
}

int compare2(char* d1, char* d2){

	int date1, date2, month1, month2, year1, year2;

	convertDateInCharsToIntegers2(d1, &date1, &month1, &year1);
	convertDateInCharsToIntegers2(d2, &date2, &month2, &year2);

	if (year1 == year2){
		if (month1 == month2){
			if (date1 == date2){
				return 0;
			}
			else if (date1 < date2){
				return -1;
			}
			else { return 1; }
		}
		else if (month1 < month2){
			return -1;
		}
		else{
			return 1;
		}
	}
	else if (year1 < year2)
		return -1;
	else
		return 1;
}
int search(struct transaction *Arr, int len, char* date) {

	int left = 0;
	int right = len - 1;
	int mid;

	while (left <= right){
		mid = (left + right) / 2;
		if (compare2(date, Arr[mid].date) == 0)
			return mid;
		else if (compare2(date, Arr[mid].date) == -1)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
bool stringCompare(char* a, char* b){

	int index;

	for (index = 0; a[index] != '\0' || b[index] != '\0'; ++index)
	if (a[index] == b[index])
		continue;
	else
		break;

	if (a[index] == '\0' && b[index] == '\0')
		return true;
	else
		return false;
}

struct transaction* sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen){

	if (A == NULL || B == NULL || ALen < 1 || BLen < 1)
		return NULL;

	struct transaction* common;
	common = (struct transaction*)calloc(10, sizeof(struct transaction));
	int commonIndex = -1;
	for (int index = 0; index < ALen; ++index){
		int positionIndex = search(B, BLen, A[index].date);
		if (B[positionIndex].amount == A[index].amount && stringCompare(B[positionIndex].description, A[index].description)){
			common[++commonIndex] = A[index];
		}
	}
	if (commonIndex == -1)
		return NULL;
	
	return common;
}
