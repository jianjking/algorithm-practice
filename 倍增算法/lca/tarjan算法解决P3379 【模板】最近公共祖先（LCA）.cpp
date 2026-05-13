#include<iostream>
#include<vector>
#include<stack>
using namespace std;
int root(int a, vector<int>& fa) {
	stack<int>f;
	while (fa[a] != a) {
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
void bin(int a, int b,vector<int>&fa) {
	int c = root(a,fa);
	int d = root(b, fa);
	if (c == d)return;
	fa[c] = d;

}
void dfs(int son, int father, vector<int>& fa, vector<bool>& vis, vector<vector<pair<int, int>>>& ques, vector<int>& ans,vector<vector<int>>graph) {
	vis[son] = true;
	for (auto& p : graph[son]) {
		if(p != father) {
			dfs(p, son, fa, vis, ques, ans, graph);
		}
	}
	for (auto& p : ques[son]) {
		if (vis[p.first])ans[p.second] = root(p.first,fa);
	}
	bin(son, father,fa);
}
int main() {
	int n, m, s;
	cin >> n >> m >> s;
	vector<vector<int>>graph(n + 1);
	for (int i = 0;i < n - 1;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int>fa(n + 1);
	vector<bool>vis(n + 1);
	vector<vector<pair<int, int>>>ques(n+1);
	vector<int>ans(m);
	for (int i = 1; i <= n; i++)
		fa[i] = i;

	for (int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		ques[a].push_back({ b,i });
		ques[b].push_back({ a,i });
	}
	dfs(s, 0, fa, vis, ques, ans,graph);
	for (auto& p : ans) {
		cout << p << '\n';
	}
}