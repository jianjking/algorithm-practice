#include<iostream>
#include<vector>
using namespace std;
vector<int>ed;
vector<int>start;
void  lazy(int i) {
	start[i]++;
}
void upstart(int a, int b, int c, int d, int num) {
	if (a <= c && b >= d) {
		lazy(num);
	}
	else {
		int mid = c + (d - c) / 2;
		if (a <= mid)upstart(a, b, c, mid, 2 * num);
		if (b > mid)upstart(a, b, mid + 1, d, 2 * num + 1);
		start[num] = start[2 * num] + start[2 * num + 1];
	}
}
void lazy1(int i) {
	ed[i]++;
}
void uped(int a, int b, int c, int d, int num) {
	if (a <= c && b >= d) {
		lazy1(num);
	}
	else {
		int mid = c + (d - c) / 2;
		if (a <= mid)uped(a, b, c, mid, 2 * num);
		if (b > mid)uped(a, b, mid + 1, d, 2 * num + 1);
		ed[num] = ed[2 * num] + ed[2 * num + 1];
	}
}
int query1(int a, int b, int c, int d, int num) {
	if (a <= c && b >= d) {
		return start[num];
	}
	else {
		int mid = c + (d - c) / 2;
		int ans = 0;
		if (a <= mid)ans += query1(a, b, c, mid, 2 * num);
		if (b > mid)ans += query1(a, b, mid + 1, d, 2 * num + 1);
		return ans;

	}
}
int query2(int a, int b, int c, int d, int num) {
	if (a <= c && b >= d) {
		return ed[num];
	}
	else {
		int mid = c + (d - c) / 2;
		int ans = 0;
		if (a <= mid)ans+=query2(a, b, c, mid, 2 * num);
		if (b > mid)ans+=query2(a, b, mid + 1, d, 2 * num + 1);
		return ans;
	
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	ed.assign(4 * n + 1, 0);
	start.assign(4 * n + 1, 0);
	for (int i = 0;i < m;i++) {
		int q, a, b;
		cin >> q >> a >> b;
		if (q == 1) {
			upstart(a,a, 1, n, 1);
			uped(b, b, 1, n, 1);
		}
		else {
			cout << query1(1, b, 1, n, 1) - query2(1, a - 1, 1, n, 1)<<endl;
		}
	}
}