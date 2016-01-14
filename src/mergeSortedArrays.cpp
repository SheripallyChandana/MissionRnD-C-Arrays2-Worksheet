/*
OVERVIEW: You are given 2 bank statements that are ordered by date - Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

void convertDateInCharsToIntegers3(char* dateInChars, int* date, int* month, int* year){

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

int compare3(char* d1, char* d2){

	int date1, date2, month1, month2, year1, year2;

	convertDateInCharsToIntegers3(d1, &date1, &month1, &year1);
	convertDateInCharsToIntegers3(d2, &date2, &month2, &year2);

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


struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {

	if (A == NULL || B == NULL || (ALen < 1 && BLen < 1))
		return NULL;

	struct transaction* common;
	common = (struct transaction*)calloc(ALen + BLen, sizeof(struct transaction));
	int commonIndex = 0;
	int AIndex = 0;
	int BIndex = 0;

	while (AIndex < ALen && BIndex < BLen){
		if (compare3(A[AIndex].date, B[BIndex].date) <= 0)
			common[commonIndex++] = A[AIndex++];
		else
			common[commonIndex++] = B[BIndex++];
	}

	while (AIndex < ALen){
		common[commonIndex++] = A[AIndex++];
	}
	while (BIndex < BLen){
		common[commonIndex++] = B[BIndex++];
	}

	if (commonIndex == -1)
		return NULL;
	return common;
}
