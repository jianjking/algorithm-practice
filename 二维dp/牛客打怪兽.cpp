#include<iostream>
#include<vector>
#include<climits>
//https://www.nowcoder.com/practice/736e12861f9746ab8ae064d4aae2d5a9
using namespace std;
vector<int>talent;
vector<int>money;
int main() {
	int n;
	cin >> n;
	talent.resize(n + 1);
	money.resize(n + 1);
	int m = 0;
	for (int i = 1;i <= n;i++) {
		scanf("%d%d", &talent[i], &money[i]);
		m += money[i];
	}
	vector<vector<int>>dp(n + 1, vector<int>(m + 1, 0));
	for (int i = 1;i <= n;i++) {
		for (int j = 0;j <= m;j++) {
			dp[i][j] = INT_MIN;
			if (dp[i - 1][j] >= talent[i]) {
				dp[i][j] = dp[i - 1][j];
			}
			if (j >= money[i] && dp[i - 1][j - money[i]] != INT_MIN) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - money[i] ]+ talent[i]);
			}
		}
	}
	for (int i = 0;i <= m;i++) {
		if (dp[n][i] != INT_MIN) {
			cout << i << endl;
			break;
		}
	}
}