#include<iostream>
#include<vector>
using namespace std;
void add(int target, int& l1, int& r1, vector<int>& queue, vector<int>& dp) {
	if (target >= 0&&dp[target]!=INT_MIN) {
		while (l1 < r1 && dp[queue[r1 - 1]] <= dp[target])r1-- ;
		queue[r1++] = target;
	}
}
void outdate(int target, int& l1, int& r1, vector<int>& queue, vector<int>& dp) {
	if (target >= 0&&l1<r1&&queue[l1]==target) {
		l1++;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, l, r;
	cin >> n >> l >> r;
	int l1, r1;
	l1 = r1 = 0;
	vector<int>dp(n + 1, INT_MIN);
	vector<int>nums(n + 1, 0);
	for (int i = 0;i <= n;i++) {
		cin >> nums[i];
	}
	dp[0] = nums[0];
	vector<int>queue(n + 1);
	for (int i = 1;i <= n;i++) {
		add(i - l, l1, r1, queue,dp);
		outdate(i - r - 1, l1, r1, queue, dp);
		dp[i] = l1 < r1 ? nums[i] + queue[l] : INT_MIN;
	}
	int ans = INT_MIN;
	for (int i = max(0, n - r + 1); i <= n;i++) {
		ans = max(ans, dp[i]);
	}
	cout << ans << '\n';
}