/*
 * B(5) = 1 x 2^2 * 5^4
 * D(5) = 1 + 2 + 4 + 10 + ... = 5467 = (2^3 - 1)/(2 - 1) * (5^5 - 1)/(5 - 1)
 * B(n) = n^n / n! * B(n-1)
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

#define MOD 1000000007

using namespace std;

// hold all primes less than a given integer n
vector<int> primes;
// hold all factorization results of B(2) up to B(n)
unordered_map<int, unordered_map<int, int>> binomial;
// hold factorization result of n!
unordered_map<int, int> factorn;

// helper function to print a map
void print_map(unordered_map<int, int> &mmap) {
	for (auto it=mmap.begin(); it!=mmap.end(); it++)
		cout << it->first << ": " << it->second << endl;
}

// find all primes smaller and equal than n
// sieve method
vector<int> compute_primes(int n) {
	vector<int> ret;
	if (n < 2) return ret;

	int limit = sqrt(n);
	vector<bool> sieve(n+1);

	for (int i=3; i<=limit; i+=2) {
		if (!sieve[i]) {
			for (int step=i<<1, j=i*i; j<=n; j+=step) {
				if (!sieve[j]) {
					sieve[j] = true;
				}
			}
		}
	}
	ret.push_back(2);
	for (int i=3; i<=n; i+=2)
		if (!sieve[i])
			ret.push_back(i);

	return ret;
}

// factorize a given integer
unordered_map<int, int> compute_factor(int n) {
	unordered_map<int, int> mmap;
	for (int i=0; i<primes.size() && n != 1; i++) {
		while (n % primes[i] == 0 && primes[i] <= n) {
			mmap[primes[i]]++;
			n /= primes[i];
		}
	}
	
	return mmap;
}

// lg(n) time compute n^p
long my_power(long n, long p) {
	long result = 1;

	n %= MOD;
	while (p) {
		if (p & 1) {
			result = (result * n) % MOD;
		}
		p >>= 1; n = ((n % MOD) * (n % MOD)) % MOD;
	}
	cout << result << endl;
	return result;
}

// logarithmic time to compute integer geometric series, 1 + x + x^2 + ... + x^n
long compute_geometric(long x, long n) {
	long result = 1;

	if (n == 0)
		return 1;
	if (n % 2)
		return (((1 + x) % MOD) * compute_geometric((x*x) % MOD, n>>1)) % MOD;
	return (1 + (x % MOD) * compute_geometric(x, n-1)) % MOD;
}

// compute the sum of all divisor of number n
long compute_d(unordered_map<int, int> &factors) {
	if (factors.empty())
		return 0;
	long sum = 1;
	for (auto it=factors.begin(); it!=factors.end(); it++) {
		/* The below code won't work because of overflow 
		 * sum *= (pow(it->first, it->second + 1) - 1) / (it->first - 1);
		 */
		/* The below code won't work because it's not the correct way! 1/(it->first-1) need some kind of inverse modula
		 * sum = ((sum % MOD) * (((my_power(it->first, it->second + 1) - 1) / (it->first - 1)) % MOD)) % MOD;
		 */
		/* The below code is too slow!
		* long sub_sum = 1;
		* long tmp = it->first;
		* for (int i=0; i<it->second; i++) {
		*	tmp %= MOD;
		*	sub_sum = (sub_sum + tmp) % MOD;
		*	tmp *= it->first;
		*	}
		*/
		sum = ((sum % MOD) * (compute_geometric(it->first, it->second) % MOD)) % MOD;
	}
	return sum;
}

// assume the keys in map2 also are in map1 with larger or equal values
// this requires `merge` to be called before `remove`
void remove(unordered_map<int, int> &map1, unordered_map<int, int> &map2) {
	for (auto it=map2.begin(); it!=map2.end(); it++) {
		map1[it->first] -= it->second;
		if (map1[it->first] == 0)
			map1.erase(it->first);
	}
}

void merge(unordered_map<int, int> &map1, unordered_map<int, int> &map2) {
	for (auto it=map2.begin(); it!=map2.end(); it++)
		map1[it->first] += it->second;
}

unordered_map<int, int> factorize_b(int n) {
	if (binomial.find(n) != binomial.end())
		return binomial[n];
	if (n == 2) {
		binomial[2] = unordered_map<int, int>{{2, 1}};
		return binomial[2];
	}
	// compute factorization of B(n-1)
	unordered_map<int, int> fb_n = factorize_b(n-1);
	// compute factorization for n
	unordered_map<int, int> fact = compute_factor(n);
	// compute factorization for n!
	merge(factorn, fact);
	// compute factorization for n^n
	for (auto it=fact.begin(); it!=fact.end(); it++)
		it->second *= n;
	// merge factors of B(n-1) and n^n
	merge(fb_n, fact);
	// remove factors of n! from B(n-1) (+) n^n
	remove(fb_n, factorn);
	
	binomial[n] = fb_n;
	return fb_n;
}

long compute_s(int n) {
	if (n <= 1)
		return n;
	// initialization
	binomial.clear();
	binomial[2] = unordered_map<int, int>{{2, 1}};
	factorn.clear();
	factorn[2] = 1;

	// compute all factorization of B(1) up to B(n)
	factorize_b(n);

	long sum = 1;
	int count = 0;
	for (auto it=binomial.begin(); it!=binomial.end(); it++)  {
		cout << "count: " << count++ << ", n: " << it->first << endl;
		sum = (sum + compute_d(it->second)) % MOD;
	}

	return sum;
}

void problem_650(void) {
	int n = 20000;
	primes = compute_primes(n);

	int ret = compute_s(20000);
	cout << "result: " << ret << endl;
}
