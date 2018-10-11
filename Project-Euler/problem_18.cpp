/*
 * Maximum path sum I
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<long> > readTriangle(char* fname) {
	vector<vector<long> > ans;
	ifstream in (fname);

	string line;
	while(getline(in, line)) {
		stringstream ss(line);
		vector<long> row;
		long num;
		while (ss >> num)
			row.push_back(num);
		ans.push_back(row);
	}
	return ans;
}

long computeMaximuPath(vector<vector<long> > triangle) {
	if (triangle.empty())
		return 0;
	if (triangle.size() == 1)
		return triangle[0][0];

	for (int i=1; i<triangle.size(); i++) {
		for (int j=0; j<triangle[i].size(); j++) {
			if (j == 0)
				triangle[i][j] += triangle[i-1][j];
			else if (j == triangle[i].size()-1)
				triangle[i][j] += triangle[i-1][j-1];
			else
				triangle[i][j] += max(triangle[i-1][j-1], triangle[i-1][j]);
		}
	}
	
	long ans =triangle.back()[0];
	for (int i=1; i<triangle.back().size(); i++)
		ans = max(ans, triangle.back()[i]);
	return ans;
}

int main(int argc, char *argv[]) {
	vector<vector<long> > triangle = readTriangle(argv[1]);
	for (int i=0; i<triangle.size(); i++) {
		for (int j=0; j<triangle[i].size(); j++)
			cout << triangle[i][j] << " ";
		cout << endl;
	}

	cout << computeMaximuPath(triangle) << endl;
	return 0;
}
