#include<iostream>
#include<vector>
using namespace std;
int mx = 0;
void dfs(int son, int father, vector<int>& dist, vector<vector<pair<int, int>>>& graph) {
	for (auto& p : graph[son]) {
		if (p.first != father)dfs(p.first, son, dist, graph);
	}
	for (auto& p : graph[son]) {
		if (p.first != father) {
			mx = max(mx, dist[son] + p.second + dist[p.first]);
			dist[son] = max(dist[son], p.second + dist[p.first]);
		}
	}

}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<vector<pair<int,int>>>graph(n + 1);
	for (int i = 1;i <n;i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ b,c });
		graph[b].push_back({ a,c });
	}
	vector<int>dist(n + 1, 0);
	dfs(1, 1, dist, graph);
	cout << mx << '\n';
}