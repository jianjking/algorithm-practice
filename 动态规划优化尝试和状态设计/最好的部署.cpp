// 最好的部署
// 一共有n台机器，编号1 ~ n，所有机器排成一排
// 你只能一台一台的部署机器，你可以决定部署的顺序，最终所有机器都要部署
// 给定三个数组no[]、one[]、both[]
// no[i] : 如果i号机器部署时，相邻没有机器部署，此时能获得的收益
// one[i] : 如果i号机器部署时，相邻有一台机器部署，此时能获得的收益
// both[i] : 如果i号机器部署时，相邻有两台机器部署，此时能获得的收益
// 第1号机器、第n号机器当然不会有两台相邻的机器
// 返回部署的最大收益
// 1 <= n <= 10^5
// 0 <= no[i]、one[i]、both[i]
// 来自真实大厂笔试，对数器验证
#include<iostream>
#include<vector>
using namespace std;
int dfs(vector<vector<int>>& dp, int l, int r, vector<int>& no, vector<int>& one, vector<int>& both) {
	if (l == r)return no[l];
	if (dp[l][r] != -1)return dp[l][r];
	int ans = 0;
	ans = max(one[l] + dfs(dp, l + 1, r, no, one, both), one[r] + dfs(dp, l, r - 1, no, one, both));
	for (int i = l + 1;i < r;i++) {
		ans = max(ans, dfs(dp, l, i - 1, no, one, both) + dfs(dp, i + 1, r, no, one, both) + both[i]);
	}
	dp[l][r] = ans;
	return ans;
  }
int f1(int n, vector<int>&no, vector<int>&one, vector<int>&both) {
	vector<vector<int>>dp(n, vector<int>(n, -1));
	return dfs(dp, 0, n - 1, no, one, both);
}
int f2(int n, vector<int>& no, vector<int>& one, vector<int>& both) {
	vector<vector<int>>dp(n, vector<int>(2, -1));
	dp[n - 1][0] = no[n-1];
	dp[n - 1][1] = one[n - 1];
	for (int i = n - 2;i >= 0;i--) {
		dp[i][0] = max(no[i] + dp[i + 1][1], one[i] + dp[i + 1][0]);
		dp[i][1] = max(one[i] + dp[i + 1][1], both[i] + dp[i + 1][0]);
	}
	return dp[0][0];
}
vector<int> create(int n) {
	vector<int>tmp(n);
	for (int i = 0;i < n;i++) {
		tmp[i] = rand() % 1000 + 10;
	}
	return tmp;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	srand(time(0));
	int n;
	for (int i = 0;i < 20000;i++) {
		int n = rand() % 100 + 1;
		vector<int>no = create(n);
		vector<int>one = create(n);
		vector<int>both = create(n);
		if (f1(n,no,one,both) != f2(n,no,one,both)) {
			cout << "测试出错" << '\n';
		}
		if (i % 100 == 0) {
			cout << "第" << i << "组测试完毕" << '\n';
		}
	 }
	cout << "测试结束" << '\n';
}