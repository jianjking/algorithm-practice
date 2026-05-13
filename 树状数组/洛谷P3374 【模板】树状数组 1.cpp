#include<iostream>
#include<vector>
using namespace std;
void add(int b, int c, vector<int>& sum) {
	int n = sum.size();
	while (b < n) {
		sum[b] += c;
		int c = b & (-b);
		b += c;
	}
}
int queriry(int a, vector<int>&sum) {
	int ans = 0;
	while (a > 0) {
		ans += sum[a];
		a -= (a & (-a));
	}
	return ans;
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<int>sum(n + 1,0);
	for (int i = 1;i <= n;i++) {
		int a;
		cin >> a;
		add(i, a, sum);
	}
	for (int i = 0;i < m;i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 1) {
			add(b, c,sum);
		}
		if (a == 2) {
			cout << queriry(c, sum) - queriry(b - 1, sum)<<endl;
		}
	}
}