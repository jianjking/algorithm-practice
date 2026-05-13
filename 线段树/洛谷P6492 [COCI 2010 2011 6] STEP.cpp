#include<iostream>
#include<vector>
using namespace std;
vector<int>tree;
vector<int>pre;
vector<int>suf;
vector<int>cur;
void up(int num, int l, int r) {
	int mid = l + (r - l) / 2;
	int i1 = 2 * num;
	int i2 = 2 * num + 1;
	cur[num] = max(cur[i1], cur[i2]);
	if (tree[mid + 1] != tree[mid])cur[num] = max(cur[num], suf[i1] + pre[i2]);
	pre[num] = pre[i1];
	if (pre[i1] == mid - l + 1 && tree[mid + 1] != tree[mid])pre[num] = pre[i1] + pre[i2];
	suf[num] = suf[i2];
	if (suf[i2] == r - mid && tree[mid + 1] != tree[mid])suf[num] = suf[i1] + suf[i2];
}
void xiugai(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d) {
		tree[a] = 1 ^ tree[a];
	}
	else {
		int mid = c + (d - c) / 2;
		if(a<=mid)xiugai(a, b, c, mid, 2 * i);
		if (b > mid)xiugai(a, b, mid + 1, d, 2 * i + 1);
		up(i, c, d);
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	tree.assign(4 * n, 0);
	cur.assign(4 * n + 1, 1);
	pre.assign(4 * n + 1, 1);
	suf.assign(4 * n + 1, 1);
	for (int i = 0;i < m;i++) {
		int a;
		cin >> a;
		xiugai(a, a, 1, n, 1);
		cout << cur[1] << endl;
	}

}