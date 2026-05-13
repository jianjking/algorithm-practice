#include<iostream>
#include<vector>
using namespace std;
int power(int n) {
	int p = 0;
	while ((1 << p) <= (n >> 1))p++;
	return p;
}
void dfs(int son, int father, int limit,vector<vector<int>>& st, vector<vector<int>>& graph, vector<int>& deep) {
	if (father == 0) {
		deep[son] = 1;
	}
	else {
		deep[son] = deep[father] + 1;
	}
	st[son][0] = father;
	for (int i = 1;i <= limit;i++) {
		if (st[son][i - 1] != 0) {
			st[son][i] = st[st[son][i - 1]][i - 1];
		}
	}
	for (auto& p : graph[son]) {
		if (p != father) {
			dfs(p, son, limit, st, graph, deep);
		}
	}
}
int lca(int a, int b, int limit,vector<int>& deep, vector<vector<int>>& st) {
	if (deep[a] < deep[b]) {
		swap(a, b);
	}
	for (int i = limit;i >= 0;i--) {
		if (st[a][i] != 0 && deep[st[a][i]] >= deep[b]) {
			a = st[a][i];
		}
	}
	if (a == b)return b;
	for (int i = limit;i >= 0;i--) {
		if (st[a][i] != st[b][i]) {
			a = st[a][i];
			b = st[b][i];
		}
	}
	return st[a][0];
}
int main() {
	int n, m;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	vector<vector<int>>graph(n + 1);
	for (int i = 0;i < n - 1;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int>deep(n + 1);
	int limit = power(n);
	vector<vector<int>>st(n + 1, vector<int>(limit + 1, 0));
	dfs(1, 0,limit,st,graph,deep);
	for (int i = 0;i < m;i++) {
		int a, b,c;
		cin >> a >> b>>c;
		int h1 = lca(a, b, limit, deep, st);
		int h2 = lca(a, c, limit, deep, st);
		int h3 = lca(b, c, limit, deep, st);

		int meet = h1;
		if (deep[h2] > deep[meet]) meet = h2;
		if (deep[h3] > deep[meet]) meet = h3;

		cout << meet << ' ' << deep[a] + deep[b] + deep[c] - deep[h1] - deep[h2] - deep[h3] << '\n';



	}
}