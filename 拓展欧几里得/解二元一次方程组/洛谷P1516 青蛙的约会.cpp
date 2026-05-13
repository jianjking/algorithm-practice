#include<iostream>
#include<vector>
using namespace std;
long long x, y;
int exgcd(int a, int b) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long g = exgcd(b,a%b);
	long long tmpx = x;
	long long tmpy = y;
	x = tmpy;
	y = tmpx - a / b * tmpy;
	return g;
}
int main() {
	long long n, m, x1, y1, l;
	cin >> x1 >> y1 >> m >> n >> l;
	long long a, b,c;
	if (x1 > y1) {
		if (n > m) {
			a = n - m;
			b = l;
			c = x1 - y1;
		}
		else{
			a = m - n;
			b = l;
			c = l - (x1 - y1);
		}
	}
	else {
		if (m > n) {
			a = m - n;
			b = l;
			c = y1 - x1;
		}
		else {
			a = n - m;
			b = l;
			c = l - (y1 - x1);
		}
	}
	if (c == 0) {
		cout << "Impossible" << '\n';
		return 0;
	}
	long long d = exgcd(a, b);
	if (c % d != 0) {
		cout << "Impossible" << '\n';
	}
	else {
		int bei = c / d;
		x *= bei;
		y *= bei;
		int diff = b / d;
		if (x <= 0) {
			x = x+(diff - x) / diff*diff;
			cout << x << '\n';
		}
		else {
			x = x-(x - 1) / diff*diff;
			cout << x << '\n';
		}
	}
}