#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n, mod;
	cin >> n >> mod;
	vector<int>ans(n + 1);
	ans[1] = 1;
	cout << 1 << endl;
	for (int i = 2;i <= n;i++) {
		ans[i] = mod - (long long)ans[mod % i] * (mod / i) % mod;
		printf("%d\n", ans[i]);
	}
}