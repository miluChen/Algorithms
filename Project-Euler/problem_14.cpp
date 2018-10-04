/*
 * which starting number, under one millon, produces the longest Collatz sequence
 */

#include <iostream>
#include <unordered_map>

using namespace std;

int collatz(unordered_map<int, int> &mmap, long n) {
	if (mmap.find(n) != mmap.end())
		return mmap[n];
	int len = 0;
	if (n % 2 == 0)
		len = collatz(mmap, n / 2);
	else
		len = collatz(mmap, 3 * n + 1);
	mmap[n] = len + 1;
	return mmap[n];
}

int main() {
	int N = 1000000;

	unordered_map<int, int> mmap;
	mmap[1] = 1;

	int max_len = 0, num = 0;
	for (int i=1; i<=N; i++) {
		int len = collatz(mmap, i);
		if (max_len < len)
			max_len = len, num = i;
	}

	cout << num << endl;
	return 0;
}
