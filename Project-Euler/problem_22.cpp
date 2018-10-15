#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int getScore(string &name) {
    int sum = 0;
    for (int i=0; i<name.size(); i++)
        sum += name[i] - 'A' + 1;
    return sum;
}

int main(int argc, char *argv[]) {
    fstream in(argv[1]);

    vector<string> names;
    string name;
    while (in >> name)
        names.push_back(name);

    sort(names.begin(), names.end());
    long ans = 0;
    for (int i=0; i<names.size(); i++)
        ans += (i+1) * getScore(names[i]);

    cout << ans << endl;

    return 0;
}
