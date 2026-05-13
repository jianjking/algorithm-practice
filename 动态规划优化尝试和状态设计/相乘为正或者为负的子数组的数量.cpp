#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
int main() {
	int n;
	cin >> n;
	vector<vector<ll>>dp(n + 1, vector<ll>(2, 0));
	for (int i = 1;i <= n;i++) {
		ll tmp;
		cin >> tmp;
		int cur = tmp > 0 ? 1 : -1;
	
		if (cur == 1) {
			dp[i][0] += dp[i - 1][0]+1;
			dp[i][1] += dp[i - 1][1];
		}
		else {
			dp[i][0] += dp[i - 1][1];
			dp[i][1] += dp[i - 1][0] + 1;
		}
	}
	ll sum1 = 0;
	ll sum2 = 0;
	for (int i = 1;i <= n;i++) {
		sum1 += dp[i][0];
		sum2 += dp[i][1];
	}
	cout << sum1 << " " << sum2 << '\n';
}