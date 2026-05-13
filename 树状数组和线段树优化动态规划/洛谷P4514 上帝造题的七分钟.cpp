#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>nums1;
vector<vector<int>>nums2;
vector<vector<int>>nums3;
vector<vector<int>>nums4;
int n, m;
int lowbit(int x) {
	return  x & (-x);
}
void add(int x1, int y1, int v) {
	int v1 = v * x1;
	int v2 = v * y1;
	int v3 = v * x1 * y1;
	for (int i = x1; i <= n; i += lowbit(i)) {
		for (int j = y1; j <= m; j += lowbit(j)) {
			nums1[i][j] += v;
			nums2[i][j] += v1;
			nums3[i][j] += v2;
			nums4[i][j] += v3;
		}
	}
}
int sum(int x, int y) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		for (int j = y; j > 0; j -= lowbit(j)) {
			ans += (x + 1) * (y + 1) * nums1[i][j] - (x + 1) * nums3[i][j] - (y + 1) * nums2[i][j] + nums4[i][j];
		}
	}
	return ans;
}
int main() {
	char ch;
	ios::sync_with_stdio(0);
	cin >> ch >> n >> m;
	nums1.assign(n + 2, vector<int>(m + 2, 0));
	nums2.assign(n + 2, vector<int>(m + 2, 0));
	nums3.assign(n + 2, vector<int>(m + 2, 0));
	nums4.assign(n + 2, vector<int>(m + 2, 0));
	while (cin >> ch) {
		if (ch == 'L') {
			int x1, y1, x2, y2, v;
			cin >> x1 >> y1 >> x2 >> y2 >> v;
			add(x1, y1, v);
			add(x2 + 1, y1, -v);
			add(x1, y2 + 1, -v);
			add(x2 + 1, y2 + 1, v);
		}
		else {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			int ans = sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
			cout << ans << '\n';
		}
	}