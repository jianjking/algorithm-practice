#include<iostream>
#include<vector>
#include<stack>
using namespace std;
vector<int>nums;
vector<int>pre;
vector<int>suf;
stack<int>f;
void up(int l, int r, int i) {
	int l1 = 2 * i;
	int mid = l + (r - l) / 2;
	int l2 = 2 * i + 1;
	pre[i] = pre[l1];
	suf[i] = suf[l2];
	if (pre[i] == mid - l + 1)pre[i] += pre[l2];
	if (suf[i] == r - mid)suf[i] += suf[l1];

}
void build(int l, int r, int i) {
	if (l == r) {
		return;
	}
	else {
		int mid = l + (r - l) / 2;
		build(l, mid, 2 * i);
		build(mid + 1, r, 2 * i + 1);
		up(l, r, i);
	}
}
void update(int a, int c, int d, int i) {
	if (c == d) {
		pre[i] ^= 1;
		suf[i] ^= 1;
	}
	else {
		int mid = c + (d - c) / 2;
		if (a <= mid)update(a, c, mid, 2 * i);
		else update(a, mid + 1, d, 2 * i + 1);
		up(c, d, i);
	}
}
int query(int a, int l, int r, int v) {
	if (l == r)return pre[v];
	int mid = l + (r - l) / 2;
	if (a <= mid) {
		if (mid - suf[2*v] + 1 <= a)return suf[2*v] + pre[2*v + 1];
		else {
			return query(a, l, mid, 2 * v);
		}
	}
	else {
		if (mid + pre[2 * v + 1] >= a)return suf[2 * v] + pre[2 * v + 1];
		else {
			return query(a, mid + 1, r, 2 * v + 1);
		}
	}
}
int main() {
	int n, m;
	cin >> n>> m;
	nums.assign(n+1, 1);
	pre.assign(4 * n + 1, 1);
	suf.assign(4 * n + 1, 1);
	build(1, n, 1);
	for (int i = 0;i < m;i++) {
		char ch;
		cin >> ch;
		if (ch == 'D') {
			int a;
			cin >> a;
			update(a, 1, n, 1);
			f.push(a);
		}
		else if (ch == 'R') {
			int a = f.top();
			f.pop();
			update(a,  1, n, 1);
		}
		else{
			int a;
			cin >> a;
			cout << query(a, 1, n, 1)<<endl;
		}
	}
}