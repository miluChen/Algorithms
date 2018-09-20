/*
 * find largest palindrome made from the product of two 3-digit numbers
 */

#include <iostream>

using namespace std;

bool isPalindrome(int n) {
	int m = 0, x = n;
	while (x > 0) {
		int tmp = x % 10;
		x /= 10;
		m = 10 * m + tmp;
	}
	return m == n;
}

int main() {
	int ans = 0;
	for (int i=999; i>=100; i--) {
		if (ans >= i * 999)
			break;
		for (int j=999; j>=100; j--) {
			int tmp = i * j;
			if (isPalindrome(tmp)) {
				ans = ans >= tmp ? ans : tmp;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
