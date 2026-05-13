#include<iostream>
#include<vector>
using namespace std;
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b,a%b);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int>lg(n + 1, -1);
	for (int i = 1;i <= n;i++) {
		lg[i] = lg[i / 2] + 1;
	}
	
	vector<vector<int>>sg(n + 1, vector<int>(lg[n] + 1));
	for (int i = 1;i <= n;i++) {
		cin >> sg[i][0];
	}
	for (int j = 1;j <= lg[n];j++) {
		for (int i = 1;i + (1 << j) <= n + 1;i++) {
			sg[i][j] = gcd(sg[i][j - 1], sg[i + (1 << (j - 1))][j - 1]);
		}
	}
	for (int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		int tmp = lg[b - a + 1];
		cout << gcd(sg[a][tmp], sg[b - (1 << tmp) + 1][tmp])<<endl;
	}
}
