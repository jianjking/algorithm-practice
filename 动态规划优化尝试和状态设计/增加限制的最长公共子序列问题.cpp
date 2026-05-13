#include<iostream>
#include<vector>
using namespace std;
string create(int n) {
	string tmp;
	for (int i = 0;i < n;i++) {
		tmp += 'a' + rand() % 26;
	}
	return tmp;
}
int dfs1(string s1, string s2, int l, int r, vector<vector<int>>& dp) {
	if (l <= 0 || r <= 0)return 0;
	if (dp[l][r] != -1)return dp[l][r];
	int ans = 0;
	if (s1[l - 1] == s2[r - 1])ans = 1 + dfs1(s1, s2, l - 1, r - 1, dp);
	else {
		ans = max(dfs1(s1, s2, l - 1, r, dp), dfs1(s1, s2, l, r - 1, dp));
	}
	dp[l][r] = ans;
	return ans;
}
int f1(string s1, string s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>>dp(n + 1, vector<int>(m + 1, -1));
	return dfs1(s1, s2, n, m, dp);
}
int dfs2(const string& s1,
	const string& s2,
	int i,            // s2 前缀长度
	int j,            // 目标子序列长度
	const vector<vector<int>>& yu,
	vector<vector<int>>& dp) {
	if (i < j)           // 前缀太短 → 不行
		return INT_MAX;
	if (j == 0)          // 要匹配空子序列 → 0 长度前缀就够
		return 0;
	if (dp[i][j] != -1)
		return dp[i][j];

	// 不用 s2[i-1]
	int ans = dfs2(s1, s2, i - 1, j, yu, dp);

	// 用 s2[i-1] 作为第 j 个字符
	int pre = dfs2(s1, s2, i - 1, j - 1, yu, dp);
	if (pre < INT_MAX) {
		int c = s2[i - 1] - 'a';
		int nxt = yu[pre][c];
		if (nxt < INT_MAX)
			ans = min(ans, nxt);
	}
	return dp[i][j] = ans;
}

int f2(string s1, string s2) {
	int n = s1.size();
	int m = s2.size();
	vector<vector<int>>yu(n + 1, vector<int>(26, INT_MAX));
	vector<int>cur(26, INT_MAX);
	vector<vector<int>>dp(m + 1, vector<int>(m + 1, -1));
	for (int i = n;i >= 0;i--) {
		yu[i] = cur;
		if (i >= 1)cur[s1[i - 1]-'a'] = i ;
	}
	for (int i = m;i >= 0;i--) {
		if (dfs2(s1, s2, m, i, yu, dp) != INT_MAX) {
			return i;
		}
	}
}
int main() {
	srand(time(0));
	for (int i = 0;i < 20000;i++) {
		int n = rand() % 100 + 1;
		int m = rand() % 100 + 1;
		string s1 = create(n);
		string s2 = create(m);
		if (f1(s1, s2) != f2(s1, s2)) {
			cout << "测试错误" << '\n';
		}
		if (i % 100 == 0) {
			cout << "第" << i << "组测试完成" << '\n';
		}
	}
	cout << "测试结束" << '\n';
}