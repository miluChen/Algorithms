/*
 * sum of digits of 2^1000
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

string stringMulti(string a, string b) {
	int m = a.size(), n = b.size();
	vector<int> ans(m+n, 0);

	for (int i=m-1; i>=0; i--) {
		for (int j=n-1; j>=0; j--) {
			int mul = (a[i] - '0') * (b[j] - '0');
			int p1 = i+j, p2 = i+j+1;
			int sum = mul + ans[p2];

			ans[p1] += sum / 10;
			ans[p2] = sum % 10;
		}
	}

	string ret;
	for (int i=0; i<ans.size(); i++) {
		if (!(ret.empty() && ans[i] == 0))
			ret.push_back(ans[i] + '0');
	}
	return ret.empty() ? "0" : ret;
}

string Power(string num, int n) {
	if (n == 1)
		return num;
	if (n % 2 == 0) {
		string tmp = Power(num, n/2);
		return stringMulti(tmp, tmp);
	}
	else {
		return stringMulti(Power(num, n-1), num);
	}
}

int main(int argc, char *argv[]) {
	int base  = atoi(argv[1]);
	int power = atoi(argv[2]);

	// log(power) multiplications
	string ans = Power(to_string(base), power);
	int ret = 0;
	for (int i=0; i<ans.size(); i++)
		ret += ans[i] - '0';

	cout << ret << endl;
	return 0;
}
