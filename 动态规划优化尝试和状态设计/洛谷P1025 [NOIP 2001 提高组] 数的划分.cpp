#include<iostream>
#include<vector>
using namespace std;
int dfs(int n, int m, vector<vector<int>>& dp) {
	if (n == 0)return 1; 
	if (m == 0)return 0;
	if (dp[n][m] != -1)return dp[n][m];
	int ans = 0;
	if (n < m) {
		ans += dfs(n, n, dp);
	}
	else {
		ans += dfs(n, m - 1, dp) + dfs(n - m, m, dp);
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	if (n < k) {
		cout << 0 << '\n';
	  }
	else if (n == k) {
		cout << 1<<'\n';
	}
	else {
		vector<vector<int>>dp(n - k+1, vector<int>(k+1, -1));
		cout << dfs(n - k, k, dp) << '\n';
	}
}