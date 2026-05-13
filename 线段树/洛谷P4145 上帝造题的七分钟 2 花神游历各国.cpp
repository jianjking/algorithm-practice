#include<iostream>
#include<vector>
using namespace std;
vector<long long>tree;
vector<long long>mx;
vector<long long>sum;
void fang(int a, int b, int c, int d, int i) {
	if (mx[i] == 1)return;
	if (c == d) {
		sum[i] = (int)sqrt(sum[i]);
		mx[i] = sum[i];
	}
	else {
		int mid = c + (d - c) / 2;
		if (mid >= a)fang(a, b, c, mid, 2 * i);
		if (b > mid)fang(a, b, mid + 1, d, 2 * i + 1);
		sum[i] = sum[2 * i]+sum[2*i+1];
		mx[i] = max(mx[2 * i], mx[2 * i + 1]);
	}
}
long long query(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d) {
		return sum[i];
	}
	else {
		long long ans = 0;
		int mid = c + (d - c) / 2;
		if (mid >= a)ans+=query(a, b, c, mid, 2 * i);
		if (b > mid)ans+=query(a, b, mid + 1, d, 2 * i + 1);
		return ans;
	}
}
void dfs(vector<long long>& nums, int l, int r, int num) {
	if (l == r) {
		sum[num] = nums[l - 1];
		mx[num] = nums[l - 1];
	}
	else {
		int mid = l + (r - l) / 2;
		dfs(nums, l, mid, 2 * num);
		dfs(nums, mid + 1, r, 2 * num + 1);
		sum[num] = sum[2 * num] + sum[2 * num + 1];
		mx[num] = max(mx[2 * num], mx[2 * num + 1]);
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	tree.assign(4*n+1,0);
	mx.assign(4 * n + 1, 0);
	sum.assign(4 * n + 1, 0);
	vector<long long>nums(n);
	for (int i = 0;i < n;i++) {
		cin >> nums[i];
	}
	dfs(nums, 1, n,1);
	int m;
	cin >> m;
	for (int i = 0;i < m;i++) {
		int k, a, b;
		cin >> k >> a >> b;
		if (a > b)swap(a, b);
		if (k == 0) {
			
			fang(a, b, 1, n, 1);
		}
		else {
			cout << query(a, b, 1, n, 1)<<endl;
		}
	}
}