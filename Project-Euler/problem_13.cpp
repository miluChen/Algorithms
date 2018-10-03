#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <algorithm>

using namespace std;

string Add(string &a, string &b) {
	string ans;
	int i = a.size()-1, j = b.size()-1, carryon = 0;
	while (i >= 0 || j >= 0) {
		int tmp = (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0) + carryon;
		ans.push_back((tmp % 10) + '0');
		carryon = tmp / 10;
		i--, j--;
	}
	if (carryon == 1)
		ans.push_back('1');
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(int argc, char *argv[]) {
	vector<string> ns;

	ifstream myfile (argv[1]);
	string line;
	while (getline(myfile, line))
		ns.push_back(line);

	string ans;
	for (int i=0; i<ns.size(); i++)
		ans = Add(ans, ns[i]);

	cout << ans << endl;

	return 0;
}
