//https://www.luogu.com.cn/problem/T386911
#include<iostream>
#include<vector>
int len = 0;
using namespace std;
int erfen(vector<int>& num, int target) {
	int l = 0;
	int r = len - 1;
	int ans = -1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (num[mid] <= target) {
			r = mid - 1;
			ans = mid;
		}
		else {
			l = mid + 1;
		}
	}
	return ans;
}
int main() {
	int n;
	cin >> n;
	vector<int>arr(n);
	for (int i = 0;i < n;i++) {
		scanf_s("%d", &arr[i]);
	}
	vector<int>num(n);
	vector<int>dp(n);
	
	for (int i = n - 1;i >= 0;i--) {
		int ans = erfen(num, arr[i]);
		if (ans == -1) {
			num[len++] = arr[i];
			dp[i] = len;
		}
		else {
			num[ans] = arr[i];
			dp[i] = ans + 1;
		}
		
	}
	vector<int>ans(len,INT_MAX);
	for (int j=0;j<n;j++) {
		if (dp[j] == len) {
			ans[0] = arr[j];
		}
		else {
			if (ans[len - dp[j] - 1] < arr[j]) {
				ans[len - dp[j]] = arr[j];
			}
		}
	}
	for (int i = 0;i<len;i++) {
		printf("%d ", ans[i]);
	}
}