/*
 * what is the index of the first term in the Fibonacci sequence to contain 1000 digits
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string strAdd(string a, string b) {
	string ans;
	int carry = 0, i = a.size()-1, j = b.size()-1;
	while (i >= 0 || j >= 0) {
		int val = (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0) + carry;
		ans.push_back((val % 10) + '0');
		carry = val / 10;
		i--; j--;
	}
	if (carry != 0)
		ans.push_back(carry + '0');
	reverse(ans.begin(), ans.end());
	return ans;
}

int firstNdigits(int n) {
	if (n <= 1)
		return 1;
	string a("1"), b("1");
	int idx = 2;
	while (b.size() < n) {
		string c = strAdd(a, b);
		a = b;
		b = c;
		idx++;
	}
	return idx;
}

void problem_25(void) {
	cout << firstNdigits(1000) << endl;
}
