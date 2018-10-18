/*
 * compute the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 */

#include "problem_s.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> KthPermutation(size_t n, long k)
{
	// perform a Euclidian division
	// keep the quotients in an array, the i-th quotient should be a number between 0 and n-i-1
	// this array is the permutation, but it needs to be adjusted
	// increment every value as many times as there are previous values that are lower or equal
	vector<int> perm(n, 0);
	long fact = 1, kk = k-1;
	for (int i=1; i<n; i++)
		fact *= i;
	// if perm[i] = 0, it means that it stores the smallest number left
	for (int i=0; i<n-1; i++) {
		perm[i] = kk/fact;
		kk %= fact;
		fact /= n-1-i;
	}
	perm[n-1] = kk/fact;	// take care of 0!

	for (int i=n-1; i>0; i--)
		for (int j=i-1; j>=0; j--)
			if (perm[j] <= perm[i])
				perm[i]++;

	return perm;
}

void problem_24(void) {
	vector<int> ans = KthPermutation(10, 1000000);
	for (int i=0; i<ans.size(); i++)
		cout << ans[i];
	cout << endl;
}
