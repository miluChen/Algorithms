/*
 * find the triangle number that has over n divisors
 * triangle number = n * (n + 1) / 2
 * if n is even, then # of divisors = #d(n/2) * #d(n+1)
 * else = #d(n) * #d((n+1)/2)
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_set<int> primes;

unordered_map<int, int> decomposite(int n) {
	unordered_map<int, int> ret;
	int i=2;
	for (auto it=primes.begin(); it!=primes.end() && n>1; it++) {
		while ((n % (*it)) == 0) {
			ret[*it]++;
			n /= *it;
		}
	}
	if (n > 1) {
		primes.insert(n);
		ret[n] = 1;
	}
	return ret;
}

int divisor(long n) {
	int ret = 0;
	for (int i=1; i<sqrt(n); i++)
		if (n % i == 0)
			ret += 2;
	if (n % int(sqrt(n)) == 0)
		ret += 1;
	return ret;
}

int methodA(int n) {
	long i = 1;
	primes.insert(2);
	while (true) {
		unordered_map<int, int> dc1, dc2;
		if (i % 2 == 0)
			dc1 = decomposite(i / 2), dc2 = decomposite(i+1);
		else
			dc1 = decomposite(i), dc2 = decomposite((i+1) / 2);

		int num = 1;
		for (auto it=dc1.begin(); it!=dc1.end(); it++) {
			num *= it->second+1;
		}
		for (auto it=dc2.begin(); it!=dc2.end(); it++) {
			num *= it->second+1;
		}
		if (num > n) {
			return i * (i + 1) / 2;
		}
		i++;
	}
	return 0;
}

int methodB(int n) {
	long i=1;
	while (divisor(i*(i+1)/2) <= n)
		i++;
	return i*(i+1)/2;
}
	

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "ERROR usage: ./a.out n method" << endl;
		return -1;
	}
	int n = atoi(argv[1]);
	int method = atoi(argv[2]);
	int num = 0;

	if (method == 1)
		num = methodA(n);
	else if (method == 2)
		num = methodB(n);
	else {
		cout << "ERROR method" << endl;
		return -1;
	}
	cout << num << endl;
	return 0;
}
