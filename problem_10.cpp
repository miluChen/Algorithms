/*
 * find the sum of all the primes below two million
 */

#include <iostream>
#include <cstdlib>
#include <bitset>

using namespace std;

int main() {
	int n = 2000000;
	bitset<2000001> values;
	values.set();

	for (int i=0; i<=n; i+=2)
		values.set(i, 0);
	values.set(1, 0);
	long ans = 2;
	for (long i=3; i<=n; i+=2) {
		if (values[i] == 1) {
			ans += i;
			for (long j=i*i; j<=n; j+=i) {
				values.set(j, 0);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
