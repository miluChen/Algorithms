/*
 * evaluate the sum of all the amicable numbers under 10000
 */

#include <iostream>
#include <cstdlib>
#include <unordered_set>

using namespace std;

int sumProperDivisor(int n) {
	int sum = 1;
	for (int i=2; i<=n/2; i++)
		if (n % i == 0)
			sum += i;
	return sum;
}

int amicablePair(int n) {
	if (n <= 1)
		return -1;
	int sum = sumProperDivisor(n);
	if (sum == n)
		return -1;
	return sumProperDivisor(sum) == n ? sum : -1;
}

int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);

	int ans = 0;
	unordered_set<int> mset;
	for (int i=1; i<=N; i++) {
		if (mset.find(i) == mset.end()) {
			int ap = amicablePair(i);
			if (ap != -1) {
				mset.insert(i);
				mset.insert(ap);
				ans += i;
				if (ap <= N)
					ans += ap;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
