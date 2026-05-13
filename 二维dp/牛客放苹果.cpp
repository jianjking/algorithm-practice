//https://www.nowcoder.com/practice/bfd8234bb5e84be0b493656e390bdebf
#include<iostream>
#include<vector>
using namespace std;
int f(int n, int m, vector<vector<int>>& dp) {
	if (n == 0)return 1;
	if (m == 0)return 0;
	if (dp[n][m] != -1)return dp[n][m];
	int ans = 0;
	if (n < m) {
		ans += f(n, n, dp);
	}
	else {
		ans += f(n, m - 1, dp) + f(n - m, m, dp);
	}
	dp[n][m] = ans;
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>>dp(n + 1, vector<int>(m + 1, -1));
	cout<<f(n, m, dp)<<'\n';
}