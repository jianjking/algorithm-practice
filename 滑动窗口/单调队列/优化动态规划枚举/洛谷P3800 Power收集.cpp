#include<iostream>
#include<vector>
using namespace std;
void add(int i, int j,vector<int>& queue,vector<vector<int>>&dp,int m, int& l, int& r) {
	if (i <=m) {
		while (l < r && dp[j][queue[r - 1]] <= dp[j][i])r--;
		queue[r++] = i;
	}
}
void outdate(int j, int i, vector<int>& queue, vector<vector<int>>& dp, int& l, int& r) {
	if (j < 0)return;
	if (l < r && queue[l] == j)l++;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k, t;
	cin >> n >> m >> k >> t;
	vector<vector<int>>dp(n + 1, vector<int>(m + 1, 0));
	for (int i = 0;i < k;i++) {
		int x, y, v;
		cin >> x >> y >> v;
		dp[x][y] = v;
	}
	for (int i = 2;i <= n;i++) {
		int l = 0;
		int r = 0;
		vector<int>queue(m + 1, 0);
		for (int j = 1;j < 1 + t;j++) {
			add(j,i-1, queue,dp, m,l, r);
		}
		for (int j = 1;j <= m;j++) {
			add(j + t, i-1, queue,dp, m, l, r);
			outdate(j - t - 1, i-1, queue, dp, l, r);
			dp[i][j] += dp[i-1][queue[l]];
		}
	}
	int ans = 0;
	for (int i = 1;i <= m;i++) {
		ans = max(ans, dp[n][i]);
	}
	cout << ans << '\n';
}