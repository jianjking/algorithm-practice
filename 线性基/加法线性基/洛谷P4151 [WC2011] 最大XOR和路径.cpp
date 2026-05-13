#include<iostream>
#include<vector>
using namespace std;
void insert(vector<long long>& nums, long long v) {
	for (int i = 61; i >= 0; i--) {
		if (((v >> i) & 1) == 1) {
			if (nums[i] == 0) { nums[i] = v; return; }
			v ^= nums[i];
		}
	}
}
void dfs(int son, int fa,long long sum, vector<bool>& vis, vector<vector<pair<int, long long>>>& graph, vector<long long>& path, vector<long long>& nums) {
	path[son] = sum;
	vis[son] = true;
	for (auto& p : graph[son]) {
		if (p.first != fa) {
			if (vis[p.first]) {
				insert(nums, path[p.first] ^ path[son] ^ p.second);
			}
			else {
				dfs(p.first, son, sum ^ p.second, vis, graph, path, nums);
			}
		}
	}
}
int main() {
	int n, m;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	vector<vector<pair<int, long long>>>graph(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		long long w;
		cin >> u >> v >> w;
		graph[u].push_back({ v,w });
		graph[v].push_back({ u,w });
	}
	vector<bool>vis(n + 1, false);
	vector<long long>path(n+1,0);
	vector<long long>nums(62, 0);
	dfs(1,0,0, vis, graph,path,nums);
	long long ans = path[n];
	for (int i = 61; i >= 0; i--) {
		ans = max(ans, ans ^ nums[i]);
	}
	cout << ans << '\n';
}