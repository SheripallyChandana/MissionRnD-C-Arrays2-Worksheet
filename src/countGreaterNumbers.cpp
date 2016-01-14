/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
void convertDateInCharsToIntegers(char* dateInChars, int* date, int* month, int* year){

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

int compare(char* d1, char* d2){
	
	int date1, date2, month1, month2, year1, year2;

	convertDateInCharsToIntegers(d1, &date1, &month1, &year1);
	convertDateInCharsToIntegers(d2, &date2, &month2, &year2);

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
int countGreaterNumbers(struct transaction *Arr, int len, char* date) {
	
	int left = 0;
	int right = len - 1;
	int mid;
	
	while (left <= right){
		mid = (left + right) / 2;
		if (compare(date,Arr[mid].date) == 0)
			break;
		else if (compare(date, Arr[mid].date) == -1)
			right = mid - 1;
		else
			left = mid + 1;
	}

	if (compare(date, Arr[mid].date) == 0){
		while (compare(Arr[mid].date ,Arr[mid + 1].date) == 0 && mid <= len - 2)
			mid++;
		return len - 1 - mid;
	}
	else if (compare(date, Arr[mid].date) == 1)
		return len - mid - 1;
	else
		return len - mid;
	return -1;
}