#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>tree;
vector<int>date;
vector<bool>change;
void lazy(int i, int v,int n) {
	tree[i] = n*v;
	date[i] = v;
	change[i] = true;
}
void down(int i,int l,int r) {
	int mid = (r - l) / 2 + l;
	lazy(2 * i, date[i],mid-l+1);
	lazy(2 * i + 1, date[i],r-mid);
}
int query(int i, int j, int a, int b, int num) {
	if (a >= i && b <= j)return tree[num];
	else {
		if (change[num]) {
			down(num,a,b);
			date[num] = 0;
			change[num] = false;
		}
		int mid = a + (b - a) / 2;
		int ans = 0;
		if (i <= mid)ans+=query(i, j, a, mid, 2 * num);
		if (j > mid)ans += query(i, j, mid + 1, b, 2 * num + 1);
		return ans;
	}
}

int findzero(int s, int r, int limit,int n) {
	int ans = 0;
	int l = s;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		int tmp = mid - s + 1 - query(s, mid, 1, n, 1);
		if (tmp >= limit) {
			r = mid - 1;
			ans = mid;
		}
	
		else {
			l = mid + 1;
		}

	}
	return ans;
}
void update(int a, int b, int c, int d, int i, int v) {
	if (a <= c && b >= d) {
		lazy(i, v,d-c+1);
	}
	else {
		if (change[i]) {
			down(i,c,d);
			change[i] = false;
			date[i] = 0;
		}
		int mid = c + (d - c)/2;
		if (a<=mid)update(a, b, c, mid, 2 * i, v);
		if (b > mid)update(a, b, mid + 1, d, 2 * i + 1, v);
		tree[i] = tree[2 * i]+tree[2 * i + 1];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int i = 0;i < t;i++) {
		int n,m;
		cin >> n>>m;
		tree.assign(4 * n + 1, 0);
		date.assign(4 * n + 1, 0);
		change.assign(4 * n + 1, false);
		for (int j = 0;j < m;j++) {
			int k, a, b;
			cin >> k >> a >> b;
			if (k == 1) {
				int tmp =n-a- query(a + 1, n, 1, n, 1);
				if (tmp == 0) {
					cout << "Can not put any one." << endl;
				}
				else {
					int c = findzero(a+1, n, 1,n);
					int d = findzero(a + 1, n, min(tmp, b), n);
					update(c, d, 1, n, 1, 1);
					cout << c-1 << " " << d-1 << endl;
				}
			}
			else{
				cout << query(a+1, b+1, 1, n, 1)<<endl;
				update(a+1, b+1, 1, n, 1, 0);
			}
		}
		cout << endl;
	}
}