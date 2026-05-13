#include<iostream>
#include<vector>
#include<climits>
using namespace std;
void dfs(int son, int father, int v, vector<vector<pair<int, int>>>& graph, vector<int>& dist, vector<int>& last, vector<int>& pre) {
	if (son == father) {
		dist[son] = 0;
		last[son] = 0;
	}
	else {
		dist[son] = v + dist[father];
		last[son] = father;
		pre[son] = v;

	}
	for (auto& p : graph[son]) {
		if (p.first != father) {
			dfs(p.first, son, p.second, graph, dist, last, pre);
		}
	}
}
void f(int son, int father, vector<int>& ju, vector<bool>& vis, vector<vector<pair<int, int>>>& graph) {
	ju[son] = 0;
	for (auto& p : graph[son]) {
		if (!vis[p.first] && p.first != father) {
			f(p.first, son, ju, vis, graph);
			ju[son] = max(ju[son], ju[p.first] + p.second);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, s;
	cin >> n >> s;
	vector<vector<pair<int, int>>>graph(n + 1);
	for (int i = 0;i < n - 1;i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ b,c });
		graph[b].push_back({ a,c });
	}
	vector<int>last(n + 1, 0);
	vector<int>dist(n + 1, 0);
	vector<int>pre(n + 1);
	dfs(1, 1, 0, graph, dist, last, pre);
	int start;
	int best = 0;
	for (int i = 1;i <= n;i++) {
		if (best < dist[i]) {
			best = dist[i];
			start = i;
		}
	}

	dfs(start, start, 0, graph, dist, last, pre);

	best = 0;
	int end;
	for (int i = 1;i <= n;i++) {
		if (best < dist[i]) {
			best = dist[i];
			end = i;
		}
	}
	vector<bool>vis(n + 1, false);
	vis[start] = true;
	for (int i = end;i != start;i = last[i]) {
		vis[i] = true;
	}
	vector<int>ju(n + 1);
	for (int i = last[end];i != start;i = last[i]) {
		f(i, i, ju, vis, graph);
	}

	vector<int>stack(n + 1);
	int l = 0;
	int r = 0;
	int sum = 0;
	int suml = 0;
	int sumr = 0;
	int ans = INT_MAX;
	for (int right = end, left = end; left;right = last[right]) {
		while (left != 0 && suml - sumr + pre[left] <= s) {
			while (l != r && ju[stack[r - 1]] < ju[left])r--;
			stack[r++] = left;
			suml += pre[left];
			left = last[left];
		}
		ans = min(ans, max(best - suml, max(ju[stack[l]], sumr)));
		if (right == stack[l])l++;
		sumr += pre[right];

	}
	cout << ans << endl;
}