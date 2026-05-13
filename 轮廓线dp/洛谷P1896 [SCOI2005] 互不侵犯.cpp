#include<iostream>
#include<vector>
using namespace std;
int get(int v, int u) {
	return (v >> u) & 1;
}
int set(int v, int u, int w) {
	return w == 1 ? v | (1 << u) : v & ~(1 << u);
}
long long dfs(int i, int j, int s, int leftup, int k, int n, int m, vector<vector<vector<vector<vector<long long>>>>>& dp) {
	if (i == n)return k == 0 ? 1 : 0;
	if (j == m) {
		return dfs(i + 1, 0, s, 0, k, n, m, dp);
	}
	if (dp[i][j][s][leftup][k] != -1)return dp[i][j][s][leftup][k];
	int l = j == 0 ? 0 : get(s, j - 1);
	int up = get(s, j);
	int rightup = (j + 1 < m) ? get(s, j + 1) : 0;

	long long ans = dfs(i, j + 1, set(s, j, 0), up, k, n, m, dp);
	if (k > 0 && l == 0 && up == 0 && leftup == 0 && rightup == 0)ans += dfs(i, j + 1, set(s, j, 1), up, k - 1, n, m, dp);
	dp[i][j][s][leftup][k] = ans;
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k;
	cin >> n >> k;
	m = n;
	// 1. 把所有 int 换成 long long
	vector<vector<vector<vector<vector<long long>>>>> dp(n, vector<vector<vector<vector<long long>>>>(m, vector<vector<vector<long long>>>(1 << m, vector<vector<long long>>(2, vector<long long>(k + 1, -1LL)
	)
	)
	)
	);

	cout << dfs(0, 0, 0, 0, k, n, m, dp) << '\n';
}