#include<bits/stdc++.h>
using namespace std;
struct node {
	int beg;
	int bac;
	int mx;
	int sum;
};
vector<node>arr;
node up(node& l, node& r) {
	node tmp;
	tmp.sum = l.sum + r.sum;
	tmp.bac = max(r.bac, r.sum + l.bac);
	tmp.beg = max(l.beg, l.sum + r.beg);
	tmp.mx = max(l.mx, max(r.mx, l.bac + r.beg));
	return tmp;
}
void build(int l, int r, int num, vector<int>& nums) {
	if (l == r) {
		arr[num].bac = nums[l];
		arr[num].beg = nums[l];
		arr[num].mx = nums[l];
		arr[num].sum = nums[l];
		return;
	}
	int mid = l + (r - l) / 2;
	build(l, mid, 2 * num, nums);
	build(mid + 1, r, 2 * num + 1, nums);
	arr[num] = up(arr[2 * num], arr[2 * num + 1]);
}
node query(int x, int y, int l, int r, int num) {
	if (x <= l && y >= r)return arr[num];
	int mid = l + (r - l) / 2;
	int ans = INT_MIN;
	if (x >= l && y <= mid)return query(x, y, l, mid, 2 * num);
	else if (x > mid && y <= r)return query(x, y, mid + 1, r, 2 * num + 1);
	else {
		node l1 = query(x, mid, l, mid, 2 * num);
		node r1 = query(mid + 1, y, mid + 1, r, 2 * num + 1);
		return up(l1, r1);
	}
}
void reset(int x, int y, int l, int r, int w, int num) {
	if (x <= l && y >= r) {
		arr[num].bac = w;
		arr[num].beg = w;
		arr[num].mx = w;
		arr[num].sum = w;
		return;
	}
	int mid = l + (r - l) / 2;
	if (x <= mid) {
		reset(x, y, l, mid, w, 2 * num);
	}
	else {
		reset(x, y, mid + 1, r, w, 2 * num + 1);
	}
	arr[num] = up(arr[2 * num], arr[2 * num + 1]);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int>nums(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	arr.assign(4 * n + 1, { 0,0,0,0 });
	build(1, n, 1, nums);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int cur;
		cin >> cur;
		if (cur == 1) {
			int l, r;
			cin >> l >> r;
			cout << query(l, r, 1, n, 1).mx << '\n';
		}
		else {
			int x, w;
			cin >> x >> w;
			reset(x, x, 1, n, w, 1);
		}
	}
}