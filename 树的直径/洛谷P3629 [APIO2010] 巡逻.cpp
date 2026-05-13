#include<iostream>
#include<vector>
using namespace std;
void dfs(int son, int father, vector<vector<int>>& graph, vector<int>& last, vector<int>& dist) {
	if (son == father) {
		dist[son] = 0;
	  }
	else {
		last[son] = father;
		dist[son] = dist[father] + 1;
	}
	for (auto& p : graph[son]) {
		if (p != father) {
			dfs(p,son, graph, last, dist);
		}
	}
}
void dp(int son, int father, vector<vector<int>>& graph, vector<bool>& vis, vector<int>& dist, int& mx) {
	dist[son] = 0;
	for (auto& p : graph[son]) {
		if (p != father) {
			dp(p, son, graph, vis, dist, mx);
			int w = (vis[son] && vis[p]) ? -1 : 1;
			mx = max(mx, dist[son] + w + dist[p]);
			dist[son] = max(dist[son], w + dist[p]);
		}
	}
}
int main() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>>graph(n+1);
	for (int i = 0;i < n - 1;i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int>last(n+1);
	vector<int>dist(n + 1);
	dfs(1, 1, graph, last, dist);
	int start;
	int best = 0;
	for (int i = 1;i <= n;i++) {
		if (dist[i] > best) {
			best = dist[i];
			start = i;
		   }
	}
	dfs(start, start, graph, last, dist);
	best = 0;
	int end;
	for (int i = 1;i <= n;i++) {
		if (dist[i] > best) {
			best = dist[i];
			end = i;
		}
	}

	if (k == 1) {
		cout << 2 * (n - 1) - best+1 << '\n';
	}
	else {
		vector<bool>vis(n + 1, false);
		vis[start] = true;
		for (int i = end;i != start;i = last[i]) {
			vis[i] = true;
		}
		int mx = 0;
		dp(1, 1, graph, vis, dist, mx);
		cout << 2 * (n - 1) - mx - best + 2 << '\n';
	}
}