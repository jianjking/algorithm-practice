//http://poj.org/problem?id=2411
#include<iostream>
#include<vector>
using namespace std;
int dfs(int i, int j, int s,int h,int w, vector<vector<vector<int>>>& dp) {
	if (i == h)return 1;
	if (j == w) {
		return dfs(i + 1, 0, s, h, w, dp);
	}
	if (dp[i][j][s] != -1)return dp[i][j][s];
	int ans = 0;
	if ((s & (1 << j)) !=0 ) {
		ans += dfs(i, j+1,s & (~(1 << j)), h, w, dp);
	}
	else {
		if(i+1<h)ans += dfs(i, j + 1, s | (1 << j), h, w, dp);
		if (j+1<w&&(s & (1 << (j + 1)) )== 0)ans += dfs(i, j + 2, s, h, w, dp);
	}
	dp[i][j][s] = ans;
	return ans;
}
int main() {
	while (true) {
		ios::sync_with_stdio(0);
		cin.tie(0);
		int h, w;
		cin >> h >> w;
		if (!h)break;
		int m = 1 << w;
		vector<vector<vector<int>>>dp(h, vector<vector<int>>(w, vector<int>(m, -1)));
		cout<<dfs(0, 0,0,h,w,dp)<<'\n';
	}
}