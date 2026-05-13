#include<iostream>
#include<vector>
using namespace std;
int main() {
	int t;
	cin >> t;
	for (int i = 0;i < t;i++) {
		int n;
		cin >> n;
		if (n % 6)cout << "October wins!" << endl;
		else cout << "Roy wins!" << endl;
	}
}