#include<iostream>
#include<vector>
using namespace std;
int main() {
	int t;
	cin >> t;
	for (int i = 0;i < t;i++) {
		int n;
		cin >> n;
		int sum1 = 0;
		int sum2 = 0;
		for (int j = 0;j < n;j++) {
			int a;
			cin >> a;
			sum1 += a;
			sum2 ^= a;
		}
		if (sum1 == n) {
			if (n % 2)cout << "Brother" << endl;
			else cout << "John" << endl;
		}
		else {
			if (sum2 != 0)cout << "John" << endl;
			else cout << "Brother" << endl;
		}
	}
}