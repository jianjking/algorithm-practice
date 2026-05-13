#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
ll l[80001];
ll r[80001];
ll sum[80001];
ll add[80001];
int cnt = 1;
void lazy(ll v, ll i, ll n) {
	sum[i] += n * v;
	add[i] += v;
}
void down(ll i, ll c  , ll d) {
	ll mid = c + (d - c) / 2;
	if (l[i] == 0)l[i] = ++cnt;
	if (r[i] == 0)r[i] = ++cnt;
	lazy(add[i], l[i], mid - c + 1);
	lazy(add[i], r[i], d - mid);
	add[i] = 0;
}
void up(ll i) {
	sum[i] = sum[l[i]] + sum[r[i]];
}
void addtion(ll a, ll b, ll v, ll c, ll d, ll i) {
	if (a <= c && b >= d) {
		lazy(v, i, d - c + 1);
	}
	else {
		if (add[i]) {
			down(i,c,d);
		}
		ll mid = c + (d - c) / 2;
		if (a <= mid) {
			if (l[i] == 0) {
				l[i] = ++cnt;
			}
			addtion(a, b, v, c, mid, l[i]);
		}
		if (b > mid) {
			if (r[i] == 0) {
				r[i] = ++cnt;
			}
			addtion(a, b, v, mid + 1, d, r[i]);
		}
		up(i);
	}
}
ll query(ll a, ll b, ll c, ll d, ll i) {
	if (a <= c && b >= d)return sum[i];
	if (add[i]) {
		down(i, c, d);
	}
	ll mid = c + (d - c) / 2;
	ll ans = 0;
	if (a <= mid) { if (l[i] != 0)ans += query(a, b, c, mid, l[i]); }
	if (b > mid) { if (r[i] != 0)ans += query(a, b, mid + 1, d, r[i]); }
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	long long n, m;
	cin >> n >> m;
	for (int i = 0;i < m;i++) {
		int tmp;
		cin >> tmp;
		if (tmp == 1) {
			ll a, b, c;
			cin >> a >> b >> c;
			addtion(a, b, c, 1, n, 1);
		}
		else {
			ll a, b;
			cin >> a >> b;
			cout << query(a, b, 1, n, 1) << endl;
		}
	}

}