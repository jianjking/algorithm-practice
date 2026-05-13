#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>graph;
vector<int>fa;
vector<int>top;
vector<int>dep;
vector<int>sz;
vector<int>son;
void dfs1(int u, int v) {
	sz[u] = 1;
	dep[u] = dep[v] + 1;
	fa[u] = v;
	for (auto& p : graph[u]) {
		if (p != v) {
			dfs1(p, u);
			sz[u] += sz[p];
			if (son[u] == 0 || sz[son[u]] < sz[p]) {
				son[u] = p;
			}
		}
	}
}
void dfs2(int u, int v) {
	top[u] = v;
	if (son[u] == 0)return;
	dfs2(son[u], v);
	for (auto& p : graph[u]) {
		if (p != fa[u] && p != son[u]) {
			dfs2(p, p);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	graph.assign(n + 1, vector<int>(0));
	fa.assign(n + 1, 0);
	top.assign(n + 1, 0);
	dep.assign(n + 1, 0);
	sz.assign(n + 1, 0);
	son.assign(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	dfs1(s, s);
	dfs2(s, s);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		while (top[x] != top[y]) {
			int x1 = top[x];
			int y1 = top[y];
			if (dep[y1] < dep[x1]) {
				x = fa[x1];
			}
			else {
				y = fa[y1];
			}
		}
		int ans = dep[x] > dep[y] ? y : x;
		cout << ans << '\n';
	}
}