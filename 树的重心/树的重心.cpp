//http://poj.org/problem?id=1655
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
using namespace std;
void dfs(int son, int father, int& best,int& num, int n, vector<int>& sz, vector<vector<int>>& graph){
	sz[son] = 1;
	int mx = INT_MIN;
	for (auto& p : graph[son]) {
		if (p == father)continue;
		dfs(p, son, best,num, n, sz, graph);
		mx = max(mx, sz[p]);
		sz[son] += sz[p];

	}
	mx = max(mx, n - sz[son]);
	if (best > mx || (best == mx && son < num)) {
		best = mx;
		num = son;
	}
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
		for (int i = 0;i < n - 1;i++) {
			int a, b;
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		int best = INT_MAX;
		vector<int>sz(n + 1);
		int num = 0;
		dfs(1, 0, best,num,n,sz,graph);
		cout << num<<" "<<best<< '\n';
	}
}