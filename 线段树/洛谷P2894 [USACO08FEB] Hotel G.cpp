#include<iostream>
#include<vector>
using namespace std;
vector<int>tree;
vector<bool>vis;
vector<int>pre;
vector<int>suf;
vector<int>cur;
void up(int l, int r, int i) {
	int mid = l + (r - l) / 2;
	int i1 = 2 * i;
	int i2 = i1 + 1;
	suf[i] = suf[i2];
	pre[i] = pre[i1];
	if (suf[i] == r - mid)suf[i] += suf[i1];
	if (pre[i] == mid - l + 1)pre[i] += pre[i2];
	cur[i] = max(max(cur[i1], cur[i2]), suf[i1] + pre[i2]);
}
void build(int l, int r, int i) {
	if (l == r) {
		pre[i] = 1;
		suf[i] = 1;
		cur[i] = 1;
	}
	else {
		int mid = l + (r - l) / 2;
		build(l, mid, 2 * i);
		build(mid + 1, r, 2 * i + 1);
		up(l, r, i);
	}
}
void lazy(int i, int v,int n) {
	pre[i] = suf[i] = cur[i] = v == 0 ? n : 0;
	vis[i] = true;
	tree[i] = v;
}
void down(int i, int l, int r) {
	int mid = l + (r - l) / 2;
	lazy(2 * i, tree[i], mid - l + 1);
	lazy(2 * i + 1, tree[i], r - mid);
	vis[i] = false;
}
void update(int a, int b, int v, int c, int d, int i) {
	if (a <= c && b >= d) {
		lazy(i,v,d-c+1);
	}
	else {
		if (vis[i]) {
			down(i, c, d);
		}
		int mid = c + (d - c) / 2;
		if (a <= mid)update(a, b, v, c, mid, 2 * i);
		if (b > mid)update(a, b, v, mid + 1, d, 2 * i + 1);
		up(c, d, i);
	}
}
int query(int k, int l, int r, int i,int n) {
	if (l == r) {
		// 用全局 [1,n]、根节点 1
		update(l, l + k - 1, 1, 1, n, 1);
		return l;
	}
	if (vis[i]) down(i, l, r);
	int mid = (l + r) / 2, i1 = 2 * i, i2 = i1 + 1;

	if (cur[i1] >= k) {
		return query(k, l, mid, i1,n);
	}
	else if (suf[i1] + pre[i2] >= k) {
		int start = mid - suf[i1] + 1;
		int end = start + k - 1;    // 【端点公式：R = L + len - 1】
		// 这里同样用全局区间
		update(start, end, 1, 1, n, 1);
		return start;
	}
	else {
		return query(k, mid + 1, r, i2,n);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	tree.assign(4*n + 1, 0);
	vis.assign(4 * n + 1, false);
	pre.assign(4 * n + 1, 0);
	suf.assign(4 * n + 1, 0);
	cur.assign(4 * n + 1, 0);
	build(1, n, 1);
	for (int i = 0;i < m;i++) {
		int a;
		cin >> a;
		if (a == 1) {
			int b;
			cin >> b;
			if (cur[1] < b)cout << 0 << endl;
			else cout << query(b, 1, n, 1,n)<<endl;
		}
		else {
			int b, c;
			cin >> b >> c;
			update(b, min(n,b+c-1), 0, 1, n, 1);
		}
	}
}