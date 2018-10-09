/*
 * number letter counts
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

char *v1[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *v2[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

int numberLetter(int n) {
	static vector<string> vs1(v1, end(v1));
	static vector<string> vs2(v2, end(v2));

	if (n == 0)
		return 0;
	if (n == 1000) // one thousand
		return 11 + numberLetter(999);

	int sum = 0;
	if (n <= vs1.size()) {
		for (int i=0; i<n; i++)
			sum += vs1[i].size();
	}
	else if (n < 100) {
		int digit1 = numberLetter(n % 10);
		int one_to_nine = numberLetter(9);
		int digit2 = 0;
		for (int i=0; i<(n/10-2); i++)
			digit2 += vs2[i].size() * 10 + one_to_nine;
		digit2 += vs2[n/10-2].size() * ((n%10) + 1);
		
		sum = digit2 + digit1 + numberLetter(19);
	}
	else if (n < 1000) {
		int digit12 = numberLetter(n % 100);
		int one_to_nintynine = numberLetter(99);
		int digit3 = 0;
		for (int i=0; i<(n/100-1); i++)
			digit3 += vs1[i].size() + 7 + (vs1[i].size() + 7 + 3) * 99 + one_to_nintynine;	// '7' stands for 'hundred', '3' stands for 'and'
		digit3 += vs1[n/100-1].size() + 7 + (vs1[n/100-1].size()+7+3) * (n%100);

		sum = digit12 + digit3 + one_to_nintynine;
	}
	return sum;
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);

	cout << numberLetter(n) << endl;

	return 0;
}
