#include<iostream>
#include<vector>
using namespace std;
vector<int>dp;
vector<int>pre;
vector<int>mx;
vector<int>add;
void up(int nums) {
	mx[nums] = max(mx[2 * nums], mx[2 * nums + 1]);
}
void lazy(int v, int nums) {
	add[nums] += v;
	mx[nums] += v;
}
void down(int nums) {

	if (add[nums] != 0) {
		int v = add[nums];
		add[nums] = 0;
		lazy(v, 2 * nums);
		lazy(v, 2 * nums + 1);
	}
}
void build(int l, int r, int nums) {
	add[nums] = 0;
	if (l == r) {
		mx[nums] = dp[l];
		add[nums] = 0;
		return;
	}
	int mid = l + (r - l) / 2;
	build(l, mid, 2 * nums);
	build(mid + 1, r, 2 * nums + 1);
	up(nums);
}
void addtion(int x, int y, int l, int r, int v, int nums) {
	if (x <= l && y >= r) {
		lazy(v, nums); return;
	}
	else {
		down(nums);
		int mid = l + (r - l) / 2;
		if (x <= mid)addtion(x, y, l, mid, v, 2 * nums);
		if (y > mid)addtion(x, y, mid + 1, r, v, 2 * nums + 1);
		up(nums);
	}
}
int query(int x, int y, int l, int r, int nums) {
	if (x <= l && y >= r) {
		return mx[nums];
	}
	down(nums);
	int mid = l + (r - l) / 2;
	int ans = INT_MIN;
	if (x <= mid) {
		ans = max(ans, query(x, y, l, mid, 2 * nums));
	}
	if (y > mid) {
		ans = max(ans, query(x, y, mid + 1, r, 2 * nums + 1));
	}

	return ans;
}
int main() {
	int n, k;
	cin >> n >> k;
	dp.assign(n + 1, INT_MIN / 4);
	dp[0] = 0;
	mx.assign(4 * n + 5, 0);
	add.assign(4 * n + 5, 0);
	vector<int>nums(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	for (int i = 1; i <= k; i++) {
		pre.assign(n + 1, 0);
		build(0, n, 1);
		for (int j = 1; j <= n; j++) {
			addtion(pre[nums[j]], j - 1, 0, n, 1, 1);
			if (j >= i) {
				dp[j] = query(i - 1, j - 1, 0, n, 1);
			}
			pre[nums[j]] = j;
		}
	}
	cout << dp[n] << '\n';
}