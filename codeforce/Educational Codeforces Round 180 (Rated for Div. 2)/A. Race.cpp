#include<iostream>
#include<vector>
using namespace std;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int u = 0;u < t;u++) {
		int a, x, y;
		cin >> a >> x >> y;
		bool an = false;
		for (int i = 1;i <= 100;i++) {
			if (abs(a - x) > abs(i - x) && abs(a - y) > abs(i - y)) {
				an = true;
				break;
			}
		}
		if (an)cout << "YES" << '\n';
		else cout << "NO" << '\n';
	}
}