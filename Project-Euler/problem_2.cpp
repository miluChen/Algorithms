/*
 * find the sum of even fibonacci numbers less than n
 */

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Error usage: ./a.out N" << endl;
		return -1;
	}

	int n = atoi(argv[1]);
	int a1 = 1, a2 = 2;
	long sum = 2;

	while (true) {
		int a3 = a1 + a2;
		if (a3 > n)
			break;
		if (a3 % 2 == 0)
			sum += a3;
		a1 = a2;
		a2 = a3;
	}
	cout << sum << endl;
	return 0;
}
