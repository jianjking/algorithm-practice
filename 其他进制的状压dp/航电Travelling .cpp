//https://acm.hdu.edu.cn/showproblem.php?pid=3001
#include<iostream>
#include<vector>
using namespace std;
int get(int s, int bit) {
	return (s / bit) % 3;
}
int set(int s, int v, int bit) {
	int pre = get(s, bit);
	return s + (v - pre) * bit;
}
void dfs(int j, int n, int s, vector<int>& sz, int bit) {
	if (j == n) {
		sz.push_back(s);
		return;
	}
	dfs(j + 1, n, set(s, 1, bit), sz, 3 * bit);
	dfs(j + 1, n, set(s, 2, bit), sz, 3 * bit);
}
int f(int i, int n,int s, vector<vector<int>>&dp,vector<vector<int>>&graph) {
	if (s == 0)return 0;
	if (dp[i][s] != -1)return dp[i][s];
	int ans = INT_MAX/2;
	for (int j = 0,bit=1;j < n;j++,bit*=3) {
		if (j != i && get(s,bit)>0&&graph[i][j] != INT_MAX) {
			ans = min(ans, graph[i][j] + f(j, n, s - bit, dp, graph));
		}
	}
	dp[i][s] = ans;
	return ans;
}
int main() {
	int n, m;
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> n >> m) {
		vector<vector<int>>graph(n+1, vector<int>(n+1, INT_MAX));
		for (int i = 0;i < m;i++) {
			int a, b, v;
			cin >> a >> b >> v;
			if (v < graph[a-1][b-1]) {
				graph[a-1][b-1] = v;
				graph[b-1][a-1] = v;
			}
		}
		vector<int>sz;
		int s = 1;
		for (int i = 0;i < n;i++)s *= 3;
		sz.reserve(s);
		dfs(0,n, 0, sz, 1);
		int ans = INT_MAX;
		vector<vector<int>>dp(n, vector<int>(s, -1));
		for (int i = 0,bit=1;i < n;i++,bit*=3) {
			for (auto& p : sz) {
				ans = min(ans, f(i,n, p-bit,dp,graph));
			}
		}
		if (ans > INT_MAX / 3)cout << -1 << '\n';
		else cout << ans << '\n';
	}
}