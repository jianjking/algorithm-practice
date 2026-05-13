//https://atcoder.jp/contests/abc236/tasks/abc236_e
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
double add(vector<double>& num) {
	int n = num.size();
	vector<vector<double>>dp(n + 1, vector<double>(2, 0));
	for (int i = n - 1;i >= 0;i--) {
		dp[i][0] = num[i] + dp[i + 1][1];
		dp[i][1] = max(dp[i + 1][1] + num[i], dp[i+1][0]);
	}
	return max(dp[0][0],dp[0][1]);
}
int main() {
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	vector<double>num(n);
	for (int i = 0;i < n;i++) {
		cin >> num[i];
	}
	vector<double>tmp = num;
	sort(tmp.begin(), tmp.end());
	int l = 0;
	int r = n - 1;
	int ans = 0;
	while (l <= r) {
		double mid = tmp[l+(r-l)/2];
		vector<double>cur(n);
		for (int i = 0;i < n;i++) {
			cur[i] = num[i] >= mid ? 1 : -1;
		}
		if (add(cur) > 0) {
			l = l + (r - l) / 2+1;
			ans = mid;
		}
		else {
			r = l + (r - l) / 2 - 1;
		}
		}
	double ans1 = 0;
	double l1 = tmp[0];
	double r1 = tmp[n - 1];

	for (int i = 0;i < 60;i++) {
		double mid = l1 + (r1 - l1) / 2;
		vector<double>cur(n);
		for (int j = 0;j < n;j++) {
			cur[j] = num[j] - mid;
		}
		if (add(cur) >= 0) {
			ans1 = mid;
			l1 = mid ;
		}
		else {
			r1 = mid ;
		}
	}
	cout << ans1 << '\n' << ans << '\n';
}