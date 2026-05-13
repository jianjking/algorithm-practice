#include<iostream>
#include<vector>
using namespace std;
int main() {
	int t;
	cin >> t;
	for (int z = 0;z < t;z++) {
		int n;
		cin >> n;
		vector<int>sg(n,0);
		vector<int>num(n);
		for (int i = n-1;i >=0;i--) {
			cin >> num[i];
		}
		for (int i = 1;i < n;i++) {
			vector<int>appera(10001, false);
			for (int j = i - 1;j >= 0;j--) {
				for (int a = j;a >= 0;a--) {
					appera[sg[j] ^ sg[a]] = true;
				}
			}
			for (int b = 0;b < 10001;b++) {
				if (!appera[b]) {
					sg[i] = b;
					break;
			   }
			}
		}
		int sum = 0;
		for (int i = 0;i < n;i++) {
			if (num[i] % 2)sum ^= sg[i];
	}
		if (!sum) { cout << -1 << " " << -1 << " " << -1 << endl << 0 << endl;continue; }
		int cnt = 0;
		int x1 = -1;
		int y1 = -1;
		int z1 = -1;
		for (int i = n - 1;i > 0;i--) {
			for (int j = i - 1;j >= 0;j--) {
				for (int a = j;a >= 0;a--) {
					int tmp = sum ^ sg[i] ^ sg[j] ^ sg[a];
					if (tmp == 0) {
						cnt++;
						if (x1 == -1) {
							x1 = n - 1 - i;
							y1 = n - 1 - j;
							z1 = n - 1 - a;
						}
					}
				}
			}
		}
		cout << x1 << " " << y1 << " " << z1 << endl<<cnt<<endl;
	}
}