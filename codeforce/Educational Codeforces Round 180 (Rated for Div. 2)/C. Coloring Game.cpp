#include<iostream>
#include<vector>
using namespace std;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	
	cin >> t;
	for (int u = 0;u < t;u++) {
		int n;
		cin >> n;
		long long sum = 0;
		vector<int>nums(n);
		for (int i = 0;i < n;i++) {
			cin >> nums[i];
		}
		for (int i = 2;i < n;i++) {
			int l = 0;
			int r = i - 1;
			while (l < r) {
				while (l < r && nums[l] + nums[r] <= max(nums[i], nums[n - 1] - nums[i]))l++;
				sum += r - l;
				r--;
			}
		}
	
		cout << sum << '\n';
	}
}