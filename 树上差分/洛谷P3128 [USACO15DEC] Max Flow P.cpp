#include<iostream>
#include<vector>
using namespace std;
int power(int n) {
	int p = 0;
	while ((1 << p) <= (n >> 1))p++;
	return p;
}
void dfs(int son, int father, int limit,vector<int>& deep, vector<vector<int>>& st, vector<vector<int>>& graph) {
	deep[son] = deep[father]+1;
	st[son][0] = father;
	for (int i = 1;i <= limit;i++) {
		st[son][i] = st[st[son][i - 1]][i - 1];
	}
	for (auto& p : graph[son]) {
		if (p != father)dfs(p, son, limit, deep, st, graph);
	}
}
void cnt(int son, int father, vector<int>& nums, vector<vector<int>>& graph) {
	for (auto& p : graph[son]) {
		if (p != father)cnt(p, son, nums, graph);
	}
	for (auto& p : graph[son]) {
		if (p != father)nums[son] += nums[p];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<vector<int>>graph(n + 1);
	for (int i = 1;i < n;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int>deep(n + 1, 0);
	int limit = power(n + 1);
	vector<vector<int>>st(n + 1, vector<int>(limit + 1,0));
	vector<int>nums(n + 1, 0);
	dfs(1, 0,limit, deep,st,graph);
	for (int i = 0;i < k;i++) {
		int a, b;
		cin >> a >> b;
		nums[a] += 1;
		nums[b] += 1;
		if (deep[a] < deep[b])swap(a, b);
		for (int i = limit;i >= 0;i--) {
			if (deep[st[a][i]] >= deep[b])a = st[a][i];
		}
		int c = 0;
		if (a == b)c = a;
		else {
			for (int i = limit;i >= 0;i--) {
				if (st[a][i] != st[b][i]) {
					a = st[a][i];
					b = st[b][i];
				}
			}
			c = st[a][0];
		}
		nums[c]--;
		nums[st[c][0]]--;
	}
	cnt(1, 0, nums, graph);
	int mx = INT_MIN;
	for (auto& p : nums) {
		mx = max(mx, p);
	}
	cout << mx << '\n';
}