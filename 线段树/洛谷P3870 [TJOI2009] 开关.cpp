#include<iostream>
#include<vector>
using namespace std;
vector<int>tree;
vector<bool>vis;
void lazy(int i, int v) {
	tree[i] = v - tree[i];
	vis[i] = !vis[i];
}
void down(int i, int l, int r) {
	int mid = l + (r - l) / 2;
	lazy(2 * i, mid - l + 1);
	lazy(2 * i + 1, r - mid);
	vis[i] = false;
}
void  update(int a, int b, int c, int d, int num) {
	if (a <= c && b >= d) {
		lazy(num, d - c+1);
	}
	else {
		int mid = c + (d - c) / 2;
		if (vis[num]) {
			down(num, c,d);
		}
		if (a <= mid)update(a, b, c, mid, 2 * num);
		if (b > mid)update(a, b, mid + 1, d, 2 * num+1);
		tree[num] = tree[2 * num] + tree[2 * num + 1];
	}
}
int query(int a, int b, int c, int d,int num) {
	if (a <= c && b >= d) {
		return tree[num];
	}
	else {
		int mid = c + (d - c) / 2;
		if (vis[num]) {
			down(num, c, d);
		}
		int ans = 0;
		if (a <= mid)ans+=query(a, b, c, mid, 2 * num);
		if (b > mid)ans+=query(a, b, mid + 1, d, 2 * num+1);
		return ans;
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	tree.assign(4 * n + 1, 0);
	vis.assign(4 * n + 1, false);
	for (int i = 0;i < m;i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 0) {
			update(b, c,1,n,1);
		}
		else {
			cout << query(b, c, 1, n,1)<<endl;
		}
	}
}