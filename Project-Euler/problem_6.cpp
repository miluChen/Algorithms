/*
 * find the differences	between sum of squares and square of sums from 1 to n
 */

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "EORROR usage: ./a.out n" << endl;
		return -1;
	}
	int n = atoi(argv[1]);

	long sum1 = (1 + n) * n / 2;
	sum1 *= sum1;
	long sum2 = n * (n + 1) * (2 * n + 1) / 6;
	cout << sum1 - sum2 << endl;
	return 0;
}
