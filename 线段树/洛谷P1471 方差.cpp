#include<iostream>
#include<vector>
using namespace std;
vector<double>sum;
vector<double>add;
vector<double>ping;
void lazy(int n, int i, double v) {
	ping[i] += 2 * v * sum[i] + v * v * n;
	add[i] += v;
	sum[i] += n * v;
}
void down(int i, int l, int r) {
	int mid = l + (r - l) / 2;
	lazy(mid - l + 1, 2 * i, add[i]);
	lazy(r - mid, 2 * i + 1, add[i]);
	add[i] = 0;
}
void addtion(int a, int b, double v, int c, int d, int i) {
	if (a <= c && b >= d)lazy(d - c + 1, i, v);
	else {
		if (add[i] != 0) {
			down(i, c, d);
		}
		int mid = c + (d - c) / 2;
		if (a <= mid)addtion(a, b, v, c, mid, 2 * i);
		if (b > mid)addtion(a, b, v, mid + 1, d, 2 * i + 1);
		sum[i] = sum[2 * i] + sum[2 * i + 1];
		ping[i] = ping[2 * i] + ping[2 * i + 1];
	}
}
double query1(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d)return sum[i];
	else {
		double ans = 0;
		if (add[i] != 0) {
			down(i, c, d);
		}
		int mid = c + (d - c) / 2;
		if (a <= mid)ans += query1(a, b, c, mid, 2 * i);
		if (b > mid)ans += query1(a, b, mid + 1, d, 2 * i + 1);
		return ans;
	}

}
double query2(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d)return ping[i];
	else {
		double ans = 0;
		if (add[i] != 0) {
			down(i, c, d);
		}
		int mid = c + (d - c) / 2;
		if (a <= mid)ans += query2(a, b, c, mid, 2 * i);
		if (b > mid)ans += query2(a, b, mid + 1, d, 2 * i + 1);
		return ans;
	}
}
void dfs(vector<double>& nums, int l, int r, int i) {
	if (l == r) {
		sum[i] = nums[l];
		ping[i] = nums[l] * nums[l];
	}
	else {
		int mid = l + (r - l) / 2;
		dfs(nums, l, mid, 2 * i);
		dfs(nums, mid + 1, r, 2 * i + 1);
		sum[i] = sum[2 * i] + sum[2 * i + 1];
		ping[i] = ping[2 * i] + ping[2 * i + 1];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	sum.assign(4 * n + 1, 0);
	ping.assign(4 * n + 1, 0);
	add.assign(4 * n + 1, 0);
	vector<double>nums(n + 1);
	for (int i = 1;i <= n;i++) {
		cin >> nums[i];
	}
	dfs(nums, 1, n, 1);
	for (int i = 0;i < m;i++) {
		int a;
		cin >> a;
		if (a == 1) {
			int b, c;
			double d;
			cin >> b >> c >> d;
			addtion(b, c, d, 1, n, 1);
		}
		else if (a == 2) {
			int b, c;
			cin >> b >> c;
			double ans = query1(b, c, 1, n, 1) / (c - b + 1);
			printf("%.4lf\n", ans);
		}
		else {
			int b, c;
			cin >> b >> c;
			double a1 = query1(b, c, 1, n, 1) / (c - b + 1);
			double a2 = query2(b, c, 1, n, 1) / (c - b + 1);
			double ans = a2 - a1 * a1;
			printf("%.4lf\n", ans);
		}
	}
}