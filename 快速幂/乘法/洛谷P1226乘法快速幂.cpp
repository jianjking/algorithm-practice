#include<iostream>
#include<vector>
using namespace std;
int f(int a, int b, int p) {
	int res = 1;
	while (b) {
		if (b & 1)res = ((long long)res * a) % p;
		a = ((long long)a * a) % p;
		b >>= 1;
	}
	return res;
}
int main() {
	int a, b, p;
	cin >> a >> b >> p;
	cout << a << "^" << b << " " << "mod " << p << "=" << f(a, b, p);
}