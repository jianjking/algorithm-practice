//https://acm.hdu.edu.cn/showproblem.php?pid=5306;
#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
vector<ll>num;
vector<ll>sum;
vector<ll>mx;
vector<ll>sem;
vector<ll>cnt;
void up(int i) {
	sum[i] = sum[2 * i] + sum[2 * i + 1];
	if (mx[2 * i] < mx[2 * i + 1]) {
		mx[i] = mx[2 * i + 1];
		cnt[i] = cnt[2 * i + 1];
		sem[i] = max(mx[2 * i], sem[2 * i + 1]);
	}
	else if (mx[2 * i] > mx[2 * i + 1]) {
		mx[i] = mx[2 * i];
		cnt[i] = cnt[2 * i];
		sem[i] = max(sem[2 * i], mx[2 * i + 1]);
	}
	else {
		mx[i] = mx[2 * i];
		cnt[i] = cnt[2 * i]+cnt[2*i+1];
		sem[i] = max(sem[2 * i], sem[2 * i + 1]);
	}
}
void build(ll l, ll r, ll i) {
	ll mid = l + (r - l) / 2;
	if (l == r) {
		sum[i] = num[l];
		cnt[i] = 1;
		mx[i] = num[l];
	}
	else {
		build(l, mid, 2 * i);
		build(mid + 1, r, 2 * i + 1);
		up(i);
	}
}
 void lazy(int i, int v) {
	if (v < mx[i]) {
		sum[i] -= ((long)mx[i] - v) * cnt[i];
		mx[i] = v;
	}
}
void down(int i) {
	lazy(i << 1, mx[i]);
	lazy(i << 1 | 1, mx[i]);
}

void update(int a, int b, int v, int c, int d, int i) {
	if (v >= mx[i])return;
	if (a <= c && b >= d && v > sem[i]) {
		lazy(i, v);
	}
	else {
		int mid = c + (d - c) / 2;
		down(i);
		if(a<=mid)update(a, b, v, c, mid, 2 * i);
		if (b > mid)update(a, b, v, mid + 1, d,2 * i + 1);
		up(i);
	}
}
ll querymx(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d)return mx[i];
	else {
		int mid = c + (d - c) / 2;
		down(i);
		ll ans = 0;
		if (a <= mid)ans=max(ans,querymx(a, b, c, mid, 2 * i));
		if (b > mid)ans = max(ans, querymx(a, b, mid + 1, d, 2 * i + 1));
		return ans;
	}
}
ll querysum(int a, int b, int c, int d, int i) {
	if (a <= c && b >= d)return sum[i];
	else {
		int mid = c + (d - c) / 2;
		down(i);
		ll ans = 0;
		if (a <= mid)ans += querysum(a, b, c, mid, 2 * i);
		if (b > mid)ans += querysum(a, b, mid + 1, d, 2 * i + 1);
		return ans;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int k = 0;k < t;k++) {
		int n, m;
		cin >> n >> m;
		num.assign(n+1,0);
		sum.assign(4 * n + 1, 0);
		mx.assign(4 * n + 1, 0);
		sem.assign(4 * n + 1, 0);
		cnt.assign(4 * n + 1, 0);
		for (int i = 1;i <= n;i++) {
			cin >> num[i];
			
		}
		build(1, n, 1);
		for (int i = 0;i < m;i++) {
			int a;
			cin >> a;
			if (a == 0) {
				int x, y,t;
				cin >> x >> y>>t;
				update(x, y, t, 1, n, 1);
			}
			else if (a == 1) {
				int x, y;
				cin >> x >> y;
				cout << querymx(x, y, 1, n, 1) << endl;
			}
			else {
				int x, y;
				cin >> x >> y;
				cout << querysum(x, y, 1, n, 1) << endl;
			}
		}
	}
}