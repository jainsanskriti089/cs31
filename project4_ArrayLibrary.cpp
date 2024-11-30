#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value); //done
int lookup(const string a[], int n, string target); //done
int positionOfMax(const string a[], int n); //done
int rotateLeft(string a[], int n, int pos); //done
int countRuns(const string a[], int n); //done
int flip(string a[], int n); //done
int differ(const string a1[], int n1, const string a2[], int n2); //done
int subsequence(const string a1[], int n1, const string a2[], int n2); //done
int lookupAny(const string a1[], int n1, const string a2[], int n2); //done
int separate(string a[], int n, string separator); //done

int differTest(const string a1[], int n1, const string a2[], int n2); //for testing

int main() {
	//personal test cases
	string empty[4] = { "", "", "", "" };
	assert(countRuns(empty, 4) == 1); //checks that it returns 1 for number of runs if all the elements are the same
	assert(lookup(empty, 4, "") == 0); //checks that it returns the first instance of the matching string
	assert(positionOfMax(empty, 4) == 0); //checks that is returns the earliest instance of the max element

	string candidate[5] = { "donald", "kamala", "jd", "tim", "jill" };
	assert(countRuns(candidate, 5) == 5); //checks that it returns the number of elements if all elements are unique
	string candidate_exclam[5] = { "donald!!!", "kamala!!!", "jd!!!", "tim!!!", "jill!!!" };
	assert(appendToAll(candidate, 5, "!!!") == 5 && differTest(candidate, 5, candidate_exclam, 5) == -2); //checks that !!! is appended to each element
	assert(appendToAll(candidate, -3, "!!!") == -1); //checks that -1 is returned when a negative number of elements is passed in 
	assert(positionOfMax(candidate, 0) == -1); //checks that -1 is returned when no elements should be considered

	assert(lookup(candidate_exclam, 5, "kamala!!!") == 1); //checks kamala!!! is found at index 1
	assert(lookup(candidate_exclam, 3, "tim") == -1); //checks that -1 is returned when the element is not found
	assert(positionOfMax(candidate_exclam, 5) == 3); //checks that the max string (last alphabetically) is tim at index 3
	assert(positionOfMax(candidate, 2) == 1); //checks that max element is found at position 1 when the elements are "donald" and "kamala"
	
	string candidate_exclam_rotated[5] = {"donald!!!", "jd!!!", "tim!!!", "jill!!!", "kamala!!!"};
	assert(rotateLeft(candidate_exclam, 5, 1) == 1 && differTest(candidate_exclam, 5, candidate_exclam_rotated, 5) == -2); //checks that the elements are rotated left

	string d1[9] = {"melania", "doug", "gwen", "gwen", "jill", "jill", "jill", "gwen", "gwen"};
	string d1sub[1] = { "gwen" };
	assert(subsequence(d1, 9, d1sub, 1) == 2); //checks that the first instance of the subsequence is returned with a subsequence length of 1
	assert(countRuns(d1, 9) == 5); //checks that the number of runs in d1 is 5
	string d1_notrotated[9] = { "melania", "doug", "gwen", "gwen", "jill", "jill", "jill", "gwen", "gwen" };
	assert(rotateLeft(d1, 7, 9) == -1 && differTest(d1, 9, d1_notrotated, 9) == -2); //checks that -1 is returned when a position past the last index is passed in and the array isn't modified
	string d1_rotated1[9] = { "doug", "gwen", "melania", "gwen", "jill", "jill", "jill", "gwen", "gwen" };
	assert(rotateLeft(d1, 3, 0) == 0 && differTest(d1, 9, d1_rotated1, 9) == -2); //checks that only the number of elements passed in are modified (only first three elements were rotated)
	string d1_rotated2[9] = { "doug", "melania", "gwen", "gwen", "jill", "jill", "jill", "gwen", "gwen" };
	assert(rotateLeft(d1, 3, 1) == 1 && differTest(d1, 9, d1_rotated2, 9) == -2); //checks that only the number of elements passed in are modified (only two elements were rotated --> basically switched)

	string folks[6] = { "kamala", "doug", "", "jill", "jd", "donald" };
	string folks_flipped1[6] = { "jill", "", "doug", "kamala", "jd", "donald" };
	assert(flip(folks, 4) == 4 && differTest(folks, 6, folks_flipped1, 6)); //checks that the array is flipped from the position given
	assert(lookup(folks, 6, "") == 1); //checks that lookup works with empty strings as well

	flip(folks, 4); //resets folks
	string group[5] = { "kamala", "doug", "donald", "", "jd" };
	assert(differ(folks, 6, group, 5) == 2); //checks that the position of the point of difference is returned
	assert(differ(folks, 2, group, 1) == 1); //checks that the length of the smaller array is returned since elements up to that point are equal
	assert(differ(folks, 2, group, 2) == 2); //checks that the length of both arrays (equal lengths) is returned since all elements are equal

	string folks_flipped2[6] = { "donald", "jd", "kamala", "doug", "", "jill" };
	assert(flip(folks, 6) == 6 && differTest(folks, 6, folks_flipped2, 6)); //checks that the entire array gets flipped
	
	string names[10] = { "kamala", "tim", "usha", "gwen", "donald", "jd" };
	string names1[10] = { "tim", "usha", "gwen" };
	assert(differ(names, 6, names1, 3) == 0); //checks that 0 is returned if none of the elements match with each other
	assert(differ(names, 6, names1, 0) == 0); //checks that 0 is returned when there are no elements to be considered in one of the arrays
	assert(subsequence(names, 6, names1, 3) == 1);  //checks that the index of where the subsequence starts is returned 
	string names2[10] = { "kamala", "gwen" };
	assert(subsequence(names, 5, names2, 2) == -1); //checks that -1 is returned when the subsequence isn't in the list
	assert(subsequence(names, 2, names1, 3) == -1); //checks that -1 is returned when the expected subsequence is longer than the original array
	
	string set1[10] = { "donald", "melania", "gwen", "tim" };
	assert(lookupAny(names, 6, set1, 4) == 1); //checks that the first instance of any element in the second array is returned
	string set2[10] = { "jill", "joe" };
	assert(lookupAny(names, 6, set2, 2) == -1); //checks that -1 is returned when the elements in the second array are not in the first
	assert(lookupAny(names, 6, set2, 0) == -1); //checks that -1 is returned when the array of elements to look for has 0 elements

	string people[6] = { "doug", "kamala", "melania", "usha", "gwen", "donald" };
	string peopleSeparated[6] = { "doug", "gwen", "donald", "kamala", "melania", "usha" };
	assert(separate(people, 6, "joe") == 3 && differTest(people, 6, peopleSeparated, 6)); //checks that array is rearranged when the separator isn't in the list
	string people2[4] = { "jill", "tim", "jd", "joe" };
	string people2Separated[4] = { "jill", "jd", "joe", "tim" };
	assert(separate(people2, 4, "joe") == 2 && differTest(people2, 4, people2Separated, 4));  //checks that array is rearranged with separator in the list

	string pattern[7] = { "doug", "melania", "kamala", "melania", "kamala", "biden", "jill" };
	string patternsub[2] = { "melania", "kamala" };
	assert(subsequence(pattern, 2, patternsub, 2) == -1); //checks that -1 is returned even if the subsequence is partially there
	assert(subsequence(pattern, 7, patternsub, 2) == 1); //checks that the first instance of the subsequence is returned with a subsequence length greater than 1
	string patternSeparated[7] = {"doug", "melania", "kamala", "melania", "kamala", "biden", "jill"};
	
	assert(separate(pattern, 1, "doug") == 1 && differTest(pattern, 7, patternSeparated, 7) == -2); //checks that the array isn't modified by the separator when only one element is in the array
	assert(separate(pattern, 0, "doug") == 0 && differTest(pattern, 7, patternSeparated, 7) == -2); //checks that the array isn't modified by the separator when zero elements are in the array
	assert(separate(pattern, 7, "melania") == 5); //checks that the position of the first instance of the separator is returned when the separator is in the array
	assert(separate(pattern, 7, "kamala") == 3); //checks that the position of the first instance of the separator is returned when the separator is in the array

	string separated[7] = { "doug", "kamala", "jill", "melania" };
	string ordered1[7] = { "doug", "kamala", "jill", "melania" };
	assert(separate(separated, 4, "biden") == 0 && differTest(separated, 4, ordered1, 4)); //checks that 0 is returned if all elements in the array are greater than the separator
	assert(separate(separated, 4, "zack") == 4 && differTest(separated, 4, ordered1, 4)); //checks that n is returned if all elements in the array are less than the separator

	string randomOrder[5] = { "biden", "kamala", "melania", "jill", "doug" };
	assert(separate(randomOrder, 4, "jack") == 1); //checks that only the number of elements passed in are rearranged by the separator value and the separator is not in the list
	
	//given test cases
	string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
	assert(lookup(h, 7, "doug") == 5); //functional check of lookup
	assert(lookup(h, 7, "donald") == 2); //functional check of lookup
	assert(lookup(h, 2, "donald") == -1); //checks that the string is not found in the array passed in (only 2 elements, not all 7)
	assert(positionOfMax(h, 7) == 3); //functional check of positionOfMax

	string g[4] = { "melania", "kamala", "jd", "usha" };
	assert(differ(h, 4, g, 4) == 2); //functional check of differ
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?"); //functional check of appendToAll
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?"); //functional check of rotateLeft

	string e[4] = { "donald", "tim", "", "doug" };
	assert(subsequence(h, 7, e, 4) == 2); //functional check of subsequence

	string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
	assert(countRuns(d, 5) == 2); //functional check of countRuns

	string f[3] = { "jd", "donald", "gwen" };
	assert(lookupAny(h, 7, f, 3) == 2); //functional check of lookUpAny
	assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd"); //functional check of flip

	assert(separate(h, 7, "jd") == 3); //functional check of separate
}

int appendToAll(string a[], int n, string value) {
	if (n < 0) return -1;
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0) return -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == target) return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n <= 0) return -1; //either number of elements is said to be negative or there are no elements to be considered (thus no max)
	
	string max = a[0];
	int maxIn = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] > max) { //updates max element only if it is greater (not equal so that the smallest index is returned)
			max = a[i];
			maxIn = i; //updates max index (respective to element)
		}
	}
	return maxIn;
}

int rotateLeft(string a[], int n, int pos) {
	if (n <= 0 || pos > n-1) return -1; //either number of elements is negative or there are none to be considered OR the position to rotate from is past the last index

	string elem = a[pos];
	for (int i = pos; i < n-1; i++) {
		a[i] = a[i + 1];
	}
	a[n - 1] = elem; //sets the last element to be the element that the rotation began at (completes the circle)
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) return -1;
	if (n == 0) return 0; //no runs in an empty array

	int numRuns = 1; //if the array has any element, then it has at least 1 run
	int curr = 0;
	for (int i = 1; i < n; i++) {
		string el = a[curr];
		if (el != a[i]) { //checks if a new run has begun if the element is no longer a consecutive repetition
			numRuns++;
			curr = i; //updates the element to be checked for a run
		}
	}
	return numRuns;
}

int flip(string a[], int n) {
	if (n < 0) return -1;
	
	int left = 0;
	int right = n - 1;
	while (left < right) {
		string temp = a[left]; //switches the matching left-right pair values
		a[left] = a[right];
		a[right] = temp;
		left++; right--; //increments left and right towards the middle
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) return -1; //if either array lengths are negative return -1
	
	int smaller; //set to the length of whichever array is shorter (avoids out of index error)
	if (n1 < n2) smaller = n1;
	else smaller = n2;
	
	for (int i = 0; i < smaller; i++) {
		if (a1[i] != a2[i]) return i;
	}

	return smaller; //returns either the shorter length or the length of both arrays if they are equal
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0 || n2 > n1) return -1; //if either array's number of elements is less than 0 OR if there are more elements in the subsequence then return -1
	if (n2 == 0) return 0;
	
	for (int i = 0; i < n1 - n2; i++) { //no point in checking past n1-n2 because there needs to be enough elements for the subsequence (and avoids out of bounds error within the second loop)
		if (a1[i] == a2[0]) { //if the element at i is the first element of the subsequence, check the following elements
			int j;
			for (j = 1; j < n2; j++) {
				if (a1[i + j] != a2[j]) break; //checks the elements following
			}
			if (j == n2) return i; //subsequnce found because the inner loop went through every element of a2 if j equals the length of a2
		}
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	/*might need to change*/ if (n1 < 0 || n2 < 0) return -1; //the length of either array is negative

	for (int i = 0; i < n1; i++) {
		string curr = a1[i]; //current element of a1
		for (int j = 0; j < n2; j++) {
			if (curr == a2[j]) return i; //checks if any of the elements in a2 matches the current element of a1
		}
	}

	return -1;
}

int separate(string a[], int n, string separator) { 
	if (n < 0) return -1;
	if (n == 0 || n == 1) return n;
	
	int left = 0;
	int right = n - 1;

	while (left <= right) {
		while (left < n && a[left] < separator) { //finds the index of the first element that is greater than the separator from the left
			left++;
		}
		while (right >= 0 && a[right] >= separator) { //finds the index of the first element that is less than the separator from the right
			right--;
		}
		if (left < right) { //switches the elements if an element that is greater than the separator is before an element that is less than the separator
			string temp = a[left];
			a[left] = a[right];
			a[right] = temp;
			left++;
			right--;
		}
	}
	return left;
}

//testing functions

int differTest(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) return -1;
	int smaller;
	if (n1 < n2) smaller = n1;
	else smaller = n2;

	for (int i = 0; i < smaller; i++) {
		if (a1[i] != a2[i]) return i;
	}

	return -2;
}