#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>tree;
vector<int>nums;
int lowbit(int x) {
	return x & (-x);
}
int query(int x, int y) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		for (int j = y; j > 0; j -= lowbit(j)) {
			ans = max(ans, tree[i][j]);
		}
	}
	return ans;
}
void update(int x, int y, int v, int n, int m) {
	for (int i = x; i < n; i += lowbit(i)) {
		for (int j = y; j < m; j += lowbit(j)) {
			tree[i][j] = max(tree[i][j], v);
		}
	}
}
int main() {
	int n, k;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	nums.assign(n, 0);
	int m = INT_MIN;
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		m = max(m, nums[i]);
	}
	tree.assign(m + k + 1, vector<int>(k + 2, 0));
	for (int i = 0; i < n; i++) {
		for (int j = k; j >= 0; j--) {
			int x = nums[i] + j;
			int y = j + 1;
			int len = query(x, y);
			update(x, y, len + 1, m + k + 1, k + 2);
		}
	}
	cout << query(m + k, k + 1) << '\n';
}