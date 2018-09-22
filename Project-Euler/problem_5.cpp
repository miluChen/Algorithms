/*
 * what is the smallest positive number that is evenly divisible by all of the numbers from 1 to n
 * n is asssumed to be smaller than 29
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

int Primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

vector<int> decomposite(int n) {
	vector<int> factors(10, 0);
	int i = 0;
	while (n > 1) {
		if (n % Primes[i] == 0) {
			factors[i]++;
			n /= Primes[i];
		}
		else
			i++;
	}
	return factors;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "ERROR usage: ./a.out n" << endl;
		return -1;
	}
	int n = atoi(argv[1]);

	vector<int> primes(10, 0);
	long ans = 1;
	for (int i=1; i<=n; i++) {
		if (ans % i != 0) {
			vector<int> factors = decomposite(i);
			for (int j=0; j<10; j++) {
				if (factors[j] > primes[j]) {
					ans *= long(pow(Primes[j], factors[j] - primes[j]));
					primes[j] = factors[j];
					if (ans % i == 0)
						break;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
