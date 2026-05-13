#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<int>next(n + 1, -1);
	next[1] = 0;
	int i = 2;
	int cn = 0;
	while (i <= n) {
		if (s[i - 1] == s[cn]) {
			next[i] = ++cn;
			i++;
		}
		else if (cn == 0) {
			next[i++] = 0;
		}
		else {
			cn = next[cn];
		}
	}
	cout << n - next[n] << endl;
}