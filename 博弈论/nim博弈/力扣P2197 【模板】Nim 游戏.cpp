#include<iostream>
#include<vector>
using namespace std;
int main() {
	int t;
	cin >> t;
	for (int i = 0;i < t;i++) {
		int n;
		cin >> n;
		int sum = 0;
		for (int j = 0;j < n;j++) {
			int a;
			cin >> a;
			sum ^= a;
		}
		if (sum == 0)cout << "No" << endl;
		else cout << "Yes" << endl;
	}
}