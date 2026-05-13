#include<iostream>
#include<vector>
using namespace std;
vector<int>dist;
vector<int>l;
vector<int>r;
vector<vector<int>>yu;
vector<int>w;
vector<int>p;
vector<int>f;
vector<int>add;
vector<int>mx;
vector<int>dp;
void lazy(int v, int nums) {
	mx[nums] += v;
	add[nums] += v;
}
void down(int nums) {
	if (add[nums]) {
		int v = add[nums];
		add[nums] = 0;
		lazy(v, 2 * nums);
		lazy(v, 2 * nums + 1);
	}
}
void up(int nums) {
	mx[nums] - max(mx[2 * nums], mx[2 * nums + 1]);
}
void addtion(int x, int y, int l, int r, int v, int nums) {
	if (x <= l && y >= r) {
		lazy(v, nums);
		return;
	}
	else {
		down(nums);
		int mid = l + (r - l) / 2;
		if (x <= mid) {
			addtion(x, y, l, mid, v, 2 * nums);
		}
		if (y > mid) {
			addtion(x, y, mid + 1, r, v, 2 * nums + 1);
		}
		up(nums);
	}

}
int query(int x, int y, int l, int r, int nums) {
	if (x <= l && y >= r) {
		return mx[nums];
	}
	else {
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
}
void build(int l,int r,int nums) {
	add[nums] = 0;
	if (l == r) {
		mx[nums] = dp[l];
		return;
	}
	int mid = l + (r - l) / 2;
	build(l, mid, 2 * nums);
	build(mid + 1, r, 2 * nums + 1);
	up(nums);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	dist.assign(n + 2, 0);
	dist[n + 1] = INT_MAX;
	for (int i = 2; i <= n; i++) {
		cin >> dist[i];
	}
	w.assign(n + 2, 0);
	p.assign(n + 1, 0);
	l.assign(n + 1, 0);
	r.assign(n + 1, 0);
	f.assign(n + 1, 0);
	yu.assign(n + 1, vector<int>(0));
	add.assign(4 * n + 7, 0);
	mx.assign(4 * n + 7, INT_MIN);
	dp.assign(n + 2, 0);
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> f[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for (int i = 1; i <= n; i++) {
		int lx = dist[i] - f[i];
		int rx = dist[i] + r[i];
		l[i] = lower_bound(dist.begin(), dist.end(), lx) - dist.begin() - 1;
		r[i] = upper_bound(dist.begin(), dist.end(), rx) - dist.begin()-1;
		yu[r[i]].push_back(i);
	}
	int sum = 0;
	for (int i = 1; i <= n + 1; i++) {
		dp[i] = w[i] + sum;
		for (auto& p1 : yu[i]) {
			sum += p[p1];
		}
	}
	for (int i = 2; i <= k + 1; i++) {
		build(1,n+1,1);
		for (int j = 1; j <= n + 1; j++) {
			if (j >= i) {
				dp[j] = max(dp[j],w[j]+ query(1, j - 1, 1, n + 1, 1));
			}
			for (auto& p1 : yu[j]) {
				int y = l[p1]-1;
				if (y < 1)continue;
				addtion(1, y, 1, n + 1, p[p1], 1);
			}
		}
	}
	cout << dp[n + 1] << '\n';
}