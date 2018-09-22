/*
 * Find the sum of all the multiples of 3 or 5 below n
 */
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Error usage: ./a.out N" << endl;
		return -1;
	}

	int n   = atoi(argv[1]);
	int sum = 0;

	for (int i=1; i<=n/3; i++) {
		int tmp = i * 3;
		if (tmp < n)
			sum += tmp;
		else
			break;
		tmp = i * 5;
		if (tmp < n && (i % 3 != 0))
			sum += tmp;
	}
	cout << "Sum of all multiples of 3 or 5 below " << n << " is: " << sum << endl;
	return 0;
}
