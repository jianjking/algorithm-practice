#include<iostream>
#include<vector>
using namespace std;
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int z = 1; z <= t; z++) {
		int n, a, b;
		cin >> n >> a >> b;
		int cha = gcd(a, b);
		cout << "Case #" << z << ":" << " ";
		if (n / cha % 2 == 1) {
			cout << "Yuwgna" << '\n';
		}
		else {
			cout << "Iaka" << '\n';
		}
	}
}