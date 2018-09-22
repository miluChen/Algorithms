/*
 * find the n-th prime number
 */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

bool isPrime(int n) {
	if (n <= 1)
		return false;
	for (int i=2; i<=sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "ERROR usage: ./a.out n" << endl;
		return -1;
	}
	int n = atoi(argv[1]);
	int count = 0, i = 1;

	while (count != n) {
		i++;
		if (isPrime(i))
			count++;
	}
	cout << i << endl;
	return 0;
}
