#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
ll x, y;
ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}
void exgcd(ll a, ll b) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	else {
		exgcd(b, a % b);
		ll tmpx = x;
		ll tmpy = y;
		x = tmpy;
		y = tmpx - a / b * tmpy;
	}
}
int main() {
	ll a, b;
	cin >> a >> b;
	exgcd(a, b);
	x %= b;
	if (x < 0)x += b;
	cout << x << '\n';
}