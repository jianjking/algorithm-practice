//https://codeforces.com/problemset/problem/1406/C
#include<iostream>
#include<vector>
using namespace std;
void   dfs(int son, int father, vector<vector<int>>& graph, vector<int>& sz,vector<int>&mx) {
	sz[son] = 1;
	int n = graph.size()-1;
	for (auto& p : graph[son]) {
		if (p != father) {
			dfs(p, son, graph, sz,mx);
			sz[son] += sz[p];
			mx[son] = max(mx[son], sz[p]);
		}
	}
	mx[son] = max(mx[son], n - sz[son]);
	
}
pair<int,int> dfs1(int son, int father, vector<vector<int>>& graph) {
	for (auto& p : graph[son]) {
		if (p != father) {
			
			return dfs1(p, son, graph);;
		}
	}
	return { father,son };
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int i = 0;i < t;i++) {
		int n;
		cin >> n;
		vector<vector<int>>graph(n + 1);
		vector<int>sz(n + 1);
		for (int i = 1;i < n;i++) {
			int a, b;
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		vector<int>mx(n + 1, INT_MIN);
		dfs(1, 1, graph,sz,mx);
		vector<int>root;
		int best = INT_MAX;  // ÐÞÕý

		
		for (int i = 1;i <= n;i++) {
			if (mx[i] < best) {
				best = mx[i];
			}
		}
		for (int i = 1;i <= n;i++) {
			if (mx[i] == best)root.push_back(i);
		}
		if (root.size() == 1) {
			cout << root[0] << " " << graph[root[0]][0] << endl;
			cout << root[0] << " " << graph[root[0]][0] << endl;
		}
		else {
			pair<int,int> aaa = dfs1(root[0], root[1], graph);
			cout << aaa.first << " " << aaa.second << endl;
			cout << root[1] << " " << aaa.second << endl;
		}

	}
}