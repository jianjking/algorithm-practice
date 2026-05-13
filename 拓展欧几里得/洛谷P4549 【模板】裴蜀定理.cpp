#include<iostream>
#include<algorithm>
using namespace std;
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	int pre;
	cin >> pre;
	if (pre < 0)pre = -pre;
	for (int i = 0; i < n - 1; i++) {
		int cur;
		cin >> cur;
		if (cur < 0)cur = -cur;
		pre = gcd(pre, cur);
	}
	cout << pre << '\n';
}