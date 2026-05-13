#include<iostream>
#include<vector>
using namespace std;
vector<long long>mx;
vector<long long>sum;
void xiu(int a, int b, int v, int c, int d, int i) {
	if (c == d) {
		sum[i] = v;
		mx[i] = v;
	}
	else {
		int mid = c + (d - c) / 2;
		if (a<=mid) {
			xiu(a, b, v, c, mid, 2 * i);
		}
		if (b > mid) {
			xiu(a, b, v, mid + 1, d, 2 * i + 1);
		}
		sum[i] = sum[2 * i] + sum[2 * i + 1];
		mx[i] = max(mx[2 * i], mx[2 * i + 1]);
	}
}
void mod(int a, int b, int v, int c, int d,int i) {
	if (mx[i] < v)return;
	if (c == d) {
		sum[i] %= v;
		mx[i] %= v;
	}
	else {
		int mid = c + (d - c) / 2;
		if (a<=mid) {
		 mod(a, b,v, c, mid, 2 * i);
		}
		if (b > mid) {
			mod(a, b, v,mid + 1, d, 2 * i + 1);
		}
		sum[i] = sum[2 * i] + sum[2 * i + 1];
		mx[i] = max(mx[2 * i], mx[2 * i + 1]);
	}
}
long long query(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d)return sum[i];
	else {
		long long ans = 0;
		int mid = c + (d - c) / 2;
		if (a<=mid) {
			ans += query(a, b, c, mid, 2 * i);
		}
		if (b > mid) {
			ans += query(a, b, mid + 1, d, 2 * i + 1);
		}
		return ans;
	}
}
void dfs(vector<long long>&nums,int l, int r, int i) {
	if (l == r) {
		sum[i] = nums[l];
		mx[i] = nums[l];
	}
	else {
		int mid = l + (r - l) / 2;
		dfs(nums, l, mid, 2 * i);
		dfs(nums, mid + 1, r, 2 * i + 1);
		sum[i] = sum[2 * i] + sum[2 * i + 1];
		mx[i] = max(mx[2 * i], mx[2 * i + 1]);
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n>>m;
	vector<long long>nums(n+1);
	mx.assign(4 * n + 1, 0);
	sum.assign(4 * n + 1, 0);
	for (int i = 1;i <= n;i++) {
		cin >> nums[i];
	}
	dfs(nums,1, n, 1);
	for (int i = 0;i < m;i++) {
		int k;
		cin >> k;
		if (k == 1) {
			int a, b;
			cin >> a >> b;
			cout << query(a, b, 1, n, 1)<<endl;
		}
		else if (k == 2) {
			int a, b, c;
			cin >> a >> b >> c;
			mod(a, b, c, 1, n, 1);
		}
		else{
			int a, b, c;
			cin >> a >> c;
			b = a;
			xiu(a, b, c, 1, n, 1);
		}
	}
}