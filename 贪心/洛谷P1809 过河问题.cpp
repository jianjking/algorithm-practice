#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int>num(n);
	for (int i = 0;i < n;i++) {
		scanf("%d", &num[i]);
	}
	sort(num.begin(), num.end());
	vector<int>dp(n);
	dp[0] = num[0];
	dp[1] = num[1];
	dp[2] = num[2] + num[0] + num[1];
	for (int i = 3;i < n;i++) {
		dp[i] = min(num[i] + num[0] + dp[i - 1], num[0] + num[1] + num[i] + num[1] + dp[i - 2]);
	}
	cout << dp[n - 1] << endl;
}