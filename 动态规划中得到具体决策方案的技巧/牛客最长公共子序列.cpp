#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
	string s1;
	string s2;
	cin >> s1 >> s2;
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>>dp(n + 1,vector<int>(m + 1, 0));
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	int k = dp[n][m];
	if (k == 0) {
		cout << -1 << endl;
		return 0;
	}
	string s;
	for (int i = n, j = m, len = k - 1;len >= 0;) {
		if (s1[i - 1] == s2[j - 1]) {
			s += s1[i - 1];
			i--;
			j--;
			len--;
		 }
		else {
			if (dp[i - 1][j] >= dp[i][j - 1]) {
				i--;
			}
			else {
				j--;
			}
		}
	}
	reverse(s.begin(), s.end());
	cout << s << endl;
}