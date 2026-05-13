#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e8;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>>grid(n, vector<int>(m));
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			cin >> grid[i][j];
		}
	}
	vector<vector<int>>dp(m+1, vector<int>(1 << m));
	vector<int>ss((1<<m), 1);
	for (int i = n - 1;i >= 0;i--) {
		dp[m] = ss;
		for (int j = m-1;j>=0;j--) {
			for (int s = 0;s < 1 << m;s++) {
				int ans = dp[j + 1][s & ~(1 << j)];
				if (grid[i][j] != 0 && (j == 0 || ((s >> (j - 1)) & 1) == 0) && (((s >> j)&1) == 0)) {
					ans =(ans+ dp[j + 1][s |(1 << j)])%mod;
				}
				dp[j][s] = ans;
			}
		}
		ss = dp[0];
	}
	cout << dp[0][0] << '\n';
}