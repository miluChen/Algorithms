/*
 * compute C_40^20 --- dynamic programming
 */

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

long compute(vector<vector<long> > &steps, int i, int j) {
	if (steps[i][j] != -1)
		return steps[i][j];
	long step = 0;
	if (i > 0)
		step += compute(steps, i-1, j);
	if (j > 0)
		step += compute(steps, i, j-1);
	steps[i][j] = step;
	return step;
}

int main(int argc, char *argv[]) {
	int m = atoi(argv[1]), n = atoi(argv[2]);
	vector<vector<long> > steps(m+1, vector<long>(n+1, -1));
	steps[0][0] = 1;

	compute(steps, m, n);
	cout << steps[m][n] << endl;
	return 0;
}
