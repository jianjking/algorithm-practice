#include<iostream>
#include<vector>
using namespace std;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<vector<int>>>st(n+1, vector<vector<int>>(n+1, vector<int>(65, false)));
	vector<vector<int>>dist(n+1, vector<int>(n+1, INT_MAX));
	for (int i = 0;i < m;i++) {
		int u,  v;
		cin >> u >> v;
		st[u][v][0] = true;
		dist[u][v] = 1;
	}
	for (int i = 1;i <= 64;i++) {
		for (int j = 1;j <= n;j++) {
			for (int z = 1;z <= n;z++) {
				for (int x = 1;x <= n;x++) {
					if (st[z][j][i - 1] && st[j][x][i - 1]) {
						st[z][x][i] = true;
						dist[z][x] = 1;
					}
				}
			}
		}
	}
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			for (int z = 1;z <= n;z++) {
				if (dist[j][i] != INT_MAX && dist[i][z] != INT_MAX) {
					dist[j][z] = min(dist[j][z], dist[j][i] + dist[i][z]);
				}
			}
		}
	}
	cout << dist[1][n] << '\n';
}