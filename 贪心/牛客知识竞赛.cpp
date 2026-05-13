//https://www.nowcoder.com/practice/2a9089ea7e5b474fa8f688eae76bc050
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<vector<int>>nums(n, vector<int>(2));
	for (int i = 0;i < n;i++) {
		cin >> nums[i][0] >> nums[i][1];
	}
	sort(nums.begin(), nums.end(), [](vector<int>& a, vector<int>& b) {
		return abs(a[0] - a[1]) < abs(b[0] - b[1]);
		});
	int max1 = nums[0][0];
	int max2 = nums[0][1];
	int ans = INT_MIN;
	for (int i = 1;i < n;i++) {
		vector<int>p = nums[i];
		if (p[0] < p[1]) {
			ans = max(ans, max1 + p[0]);
		}
		else {
			ans = max(ans, max2 + p[1]);
		}
		max1 = max(p[0], max1);
		max2 = max(max2, p[1]);
	}
	cout<<(double) ans / 2<<endl;
}