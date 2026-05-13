#include<iostream>
#include<vector>
#include<stack>
using namespace std;
int root(int a, vector<int>& fa) {
	stack<int>f;
	while (a != fa[a]) {
		f.push(a);
		a = fa[a];
	}
	while (!f.empty()) {
		int tmp = f.top();
		f.pop();
		fa[tmp] = a;
	}
	return a;
}
void dfs(int son, int father, vector<int>& dist, vector<vector<int>>& graph,int&mx) {
	
	for (auto& p : graph[son]) {
		if (p != father) {
			dfs(p, son, dist, graph, mx);
			mx = max(mx, dist[son] + 1 + dist[p]);
			dist[son] = max(dist[son], 1 + dist[p]);
		}
	}
}
void merge(int a, int b, vector<int>& fa) {
	int c = root(a, fa);
	int d = root(b, fa);
	if (c == d)return;
	fa[c] = d;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m,q;
	cin >> n>>m>>q;
	vector<int>fa(n + 1);
	vector<int>sz(n + 1, 0);
	vector<vector<int>>graph(n + 1);
	for (int i = 1;i <= n;i++) {
		fa[i] = i;
	}
	for (int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
		merge(a, b, fa);
	}
	vector<int>dist(n + 1, 0);
	for (int i = 1;i <= n;i++) {
		int mx = 0;
		if (i == fa[i]) { dfs(i, i, dist, graph, mx);sz[i] = mx; }
	}
	for (int i = 0;i < q;i++) {
		int p;
		cin >> p;
		if (p == 1) {
			int a;
			cin >> a;
			cout << sz[root(a, fa)] << endl;
		}
		else {
			int x1, x2;
			cin >> x1 >> x2;
			int y1 = root(x1, fa);
			int y2 = root(x2, fa);
			if (y1 == y2)continue;
			fa[y1] = y2;
			sz[y2] = max(sz[y2], max(sz[y1], (sz[y1] + 1) / 2 + (sz[y2] + 1) / 2 + 1));
		}
	}
}