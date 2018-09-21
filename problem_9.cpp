/*
 * find abc, where a^2 + b^2 = c^2 and a + b + c = 1000
 * 1000000 - 2000a - 2000b + 2ab = 0
 * 500000 - 1000a - 1000b + ab = 0
 * 500 = a + b - ab/1000; 1000 = 2^3*5^3
 */

#include <iostream>

using namespace std;

int main() {
	for (int i=1; i<=499; i++) {
		for (int j=i+1; j<=500; j++) {
			if ((i * j % 1000 == 0) && (500 == i + j - i*j/1000)) {
				cout << i * j * (1000 - i - j) << endl;
				break;
			}
		}
	}
	return 0;
}
