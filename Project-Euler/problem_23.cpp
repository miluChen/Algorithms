/*
 * find the sum of all the positive integers which can not be written as the sum of two abundant numbers
 */

#include <iostream>
#include <unordered_set>

#define UPPERLIMIT 28123

using namespace std;

bool isAbundant(int n) {
	int sum = 0;
	for (int i=1; i<=n/2; i++)
		if (n % i == 0)
			sum += i;
	return sum > n;
}

int main() {
	long ans = 0;

	unordered_set<int> mset;
	for (int i=1; i<=UPPERLIMIT; i++) {
		ans += i;
		for (auto it=mset.begin(); it!=mset.end(); it++) {
			if (mset.find(i - (*it)) != mset.end()) {
				ans -= i;
				// cout << "add: " << i << endl;
				break;
			}
		}
		if (isAbundant(i)) {
			mset.insert(i);
			//cout << i << endl;
		}
	}
	cout << ans << endl;
	return 0;
}
