#include<iostream>
#include<vector>
using namespace std;
using ll = long long;

ll x, y;
ll exgcd(ll a, ll b) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll g = exgcd(b, a % b);
	ll tmpx = x;
	ll tmpy = y;
	x = tmpy;
	y = tmpx - (a / b) * tmpy;
	return g;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	for (int z = 0; z < t; z++) {
		ll a, b, c;
		cin >> a >> b >> c;
		ll gcd = exgcd(a, b);
		if (c % gcd != 0) {
			cout << -1 << '\n';
			continue;
		}
		x = x * (c / gcd);
		y = y * (c / gcd);
		ll diff1 = b / gcd;
		ll diff2 = a / gcd;

		if (x <= 0) {
			ll bei = (diff1 - x) / diff1;
			x += bei * diff1;
			y -= diff2 * bei;
		}
		else {
			ll bei = (x - 1) / diff1;
			x -= bei * diff1;
			y += diff2 * bei;
		}

		if (y <= 0) {
			ll bei = (diff2 - y) / diff2;
			y += diff2 * bei;
			cout << x << " " << y << '\n';
		}
		else {
			ll bei = (y - 1) / diff2;
			ll xmin = x;
			ll ymax = y;
			ll xmax = x + bei * diff1;
			ll ymin = y - bei * diff2;
			cout << (bei + 1) << " " << xmin << " " << ymin << " " << xmax << " " << ymax << '\n';
		}
	}
}
