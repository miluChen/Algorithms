/*
 * find the largest prime factor of an integer
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool isPrime(long n) {
	if (n == 1)
		return false;
	for (long i=2; i<=sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Error: usage ./a.out number" << endl;
		return -1;
	}

	string sn(argv[1]);
	long n = stol(sn);

	for (long i=sqrt(n); i>=1; i--) {
		if (n % i == 0) {
			if (isPrime(i)) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}
