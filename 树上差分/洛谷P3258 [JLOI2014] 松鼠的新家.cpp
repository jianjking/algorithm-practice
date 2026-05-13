#include<iostream>
#include<vector>
using namespace std;
int power(int n) {
	int p = 0;
	while ((1 << p) <= (n >> 1))p++;
	return p;
}
void dfs(int son, int father,int limit, vector<int>& deep, vector<vector<int>>& st, vector<vector<int>>& graph) {
	deep[son] = deep[father] + 1;
	st[son][0] = father;
	for (int i = 1;i <= limit;i++) {
		st[son][i] = st[st[son][i - 1]][i - 1];
	}
	for (auto& p : graph[son]) {
		if (p != father) {
			dfs(p, son, limit, deep, st, graph);
		}
	}
}
void bfs(int son, int father, vector<int>& cnt, vector<vector<int>>& graph) {
	for (auto& p : graph[son]) {
		if (p != father)bfs(p, son, cnt, graph);
	}
	for (auto& p : graph[son]) {
		if (p != father)cnt[son] += cnt[p];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<vector<int>>graph(n + 1);
	vector<int>nums(n);
	for (int i = 0;i < n;i++) {
		cin >> nums[i];
	}
	for (int i = 0;i < n-1;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int>deep(n + 1, 0);
	int limit = power(n+1);
	vector<vector<int>>st(n + 1, vector<int>(limit + 1, 0));
	dfs(1, 0, limit,deep, st,graph);
	vector<int>cnt(n + 1, 0);
	for (int i = 0;i < n - 1;i++) {
		int a1 = nums[i];
		int a2 = nums[i + 1];
		cnt[a1]++;
		cnt[a2]++;
		if (deep[a1] < deep[a2]) {
			swap(a1, a2);
		}
		for (int i = limit;i >= 0;i--) {
			if (deep[st[a1][i]] >= deep[a2])a1 = st[a1][i];
		}
		int c;
		if (a1 == a2) {
			c = a1;
		}
		else {
			for (int j = limit;j >= 0;j--) {
				if (st[a1][j] != st[a2][j]) {
					a1 = st[a1][j];
					a2 = st[a2][j];
				}
		}
			c = st[a1][0];
		}
		cnt[c]--;
		cnt[st[c][0]]--;
		
	}
	bfs(1, 0, cnt, graph);
	int sum = 0;
	for (auto& p : cnt) {
		sum += p;
	}
	for (int i = 1;i < n;i++) {
		cnt[nums[i]]--;
	}
	for (int i = 1;i <= n;i++) {
		cout << cnt[i] << '\n';
	}
}