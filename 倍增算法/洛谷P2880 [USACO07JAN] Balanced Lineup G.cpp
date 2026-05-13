#include<iostream>
#include<vector>
using namespace std;
int power(int m) {
	int p = 0;
	while ((1 << p) <= (m >> 1)) {
		p++;
	}
	return p;
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
	vector<int>nums(n+1);
	for (int i = 1;i <= n;i++) {
		cin >> nums[i];
	}
	int limit = power(n);
	vector<vector<int>>stmx(n + 1, vector<int>(limit + 1));
	vector<vector<int>>stmn(n + 1, vector<int>(limit + 1));
	for (int i = 1;i <= n;i++) {
		stmx[i][0] = nums[i];
		stmn[i][0] = nums[i];

	}
	for (int j = 1;j <= limit;j++) {
		for (int i = 1;i + (1 << j) <= n + 1
			;i++) {
			stmx[i][j] = max(stmx[i][j - 1], stmx[i + (1 << (j-1))][j - 1]);
			stmn[i][j] = min(stmn[i][j - 1], stmn[i + (1 << (j - 1))][j - 1]);
		}
	}
	for (int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		int tmp = lg[b - a + 1];
		cout << max(stmx[a][tmp], stmx[b - (1<<tmp) + 1][tmp]) - min(stmn[a][tmp], stmn[b - (1<<tmp) + 1][tmp]) << endl;
	}
}
