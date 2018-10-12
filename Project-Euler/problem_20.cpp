/*
 * find the sum of the digits in the number 100!
 */

#include <iostream>
#include <cstdlib>
#include <string>
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

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	string ans("1");

	for (int i=2; i<=n; i++)
		ans = stringMulti(ans, to_string(i));

	int ret = 0;
	for (int i=0; i<ans.size(); i++)
		ret += ans[i] - '0';
	cout << ret << endl;

	return 0;
}
