#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
int root(int a, vector<int>& fa) {
	stack<int>tmp;
	while (a != fa[a]) {
		tmp.push(a);
		a = fa[a];
	}
	while (!tmp.empty()) {
		int b = tmp.top();
		tmp.pop();
		fa[b] = a;
	}
	return a;
}
int lg(int n) {
	int p = 0;
	while ((1 << p) <= (n >> 1))p++;
	return p;
}
void dfs(int son, int father, int v, int limit, vector<bool>& vis, vector<vector<pair<int, int>>>& graph, vector<int>& deep, vector<vector<int>>& st, vector<vector<int>>& stmn) {
	vis[son] = true;
	if (father == 0)deep[son] = 1;
	else deep[son] = deep[father] + 1;
	st[son][0] = father;
	stmn[son][0] = v;
	for (int i = 1;i <= limit;i++) {
		if (st[son][i - 1] != 0) {
			st[son][i] = st[st[son][i - 1]][i - 1];
			stmn[son][i] = min(stmn[son][i - 1], stmn[st[son][i - 1]][i - 1]);
		}
	}
	for (auto& p : graph[son])
	{      if(!vis[p.first])
		dfs(p.first, son, p.second, limit, vis, graph, deep, st, stmn);
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>>edges(m,vector<int>(3));
	for (int i = 0;i < m;i++) {
		cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
	}
	sort(edges.begin(), edges.end(), [](auto a, auto b) {
		return a[2] > b[2];
		});
	vector<int>fa(n+1);
	for (int i = 1;i <= n;i++) {
		fa[i] = i;
	}
	vector<vector<pair<int, int>>>graph(n+1);
	for (int i = 0;i < m;i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		int w = edges[i][2];
		int c = root(u, fa);
		int d = root(v, fa);
		if (c == d)continue;
		graph[u].push_back({ v,w });
		graph[v].push_back({ u,w });
		fa[c] = d;
	}
	vector<bool>vis(n + 1,false);
	int limit = lg(n);
	vector<vector<int>>st(n + 1, vector<int>(limit+1, 0));
	vector<int>deep(n + 1);
	vector<vector<int>>stmn(n + 1, vector<int>(limit+1));
	for (int i = 1;i <= n;i++) {
		if (!vis[i]) {
			dfs(i, 0,INT_MAX,limit,vis,graph,deep,st,stmn);
		}
	}
	int q;
	cin >> q;
	for(int i=0;i<q;i++){
		int a, b;
		cin >> a >> b;
		int c = root(a, fa);
		int d = root(b, fa);
		if (c != d) { 
			cout << -1 << '\n';
			continue;
		}
		if (deep[a] < deep[b]) {
			swap(a, b);
		}
		int ans = INT_MAX;
		for (int i = limit;i >= 0;i--) {
			if (st[a][i] != 0 && deep[st[a][i]] >= deep[b]) {
				ans = min(ans, stmn[a][i]);
				a = st[a][i];
			
			}
		}
		if (a == b) {
			cout << ans << endl;
			continue;
		}
		for (int i = limit;i >= 0;i--) {
			if (st[a][i] != st[b][i]) {
				ans = min(ans, min(stmn[a][i], stmn[b][i]));
				a = st[a][i];
				b = st[b][i];
			}
		}
		ans = min(ans, min(stmn[a][0], stmn[b][0]));
		cout << ans << endl;
	
	}
}