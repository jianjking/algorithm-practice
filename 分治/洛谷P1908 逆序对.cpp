#include<iostream>
#include<vector>
using namespace std;
long long merge(int l, int r, vector<long long>& arr) {
	if (l == r)return 0;
	int mid = l + (r - l) / 2;
	long long ans = merge(l, mid, arr) + merge(mid + 1, r, arr);
	vector<long long>tmp(r - l + 1);
	int l1 = l;
	int cnt = 0;
	int r1 = mid + 1;
	while (l1 <= mid && r1 <= r) {
		if (arr[l1] > arr[r1]) {
			tmp[cnt++] = arr[r1++];
			ans += mid - l1 + 1;
		}
		else {
			tmp[cnt++] = arr[l1++];
		}
	}
	while (l1 <= mid) {
		tmp[cnt++] = arr[l1++];

	}
	while (r1 <= r) {
		tmp[cnt++] = arr[r1++];
	}
	for (int i = 0;i <= r - l;i++) {
		arr[i + l] = tmp[i];
	}
	return ans;
}
int main() {
	int n;
	cin >> n;
	vector<long long>nums(n);
	for (int i = 0;i < n;i++) {
		cin >> nums[i];
	}
	cout << merge(0, n - 1, nums) << endl;
}