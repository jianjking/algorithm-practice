#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	vector<long long>weight(n + 1, 0);
	vector<long long>nums(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> nums[i] >> weight[i];
	}
	int row = 1;
	long long sum = 0;
	for (int col = 63; col >= 0; col--) {
		int mx = -1;
		for (int r = row; r <= n; r++) {
			if (((nums[r] >> col) & 1) == 1) {
				if (mx == -1)mx = r;
				if (weight[r] > weight[mx])mx = r;
			}
		}
		if (mx == -1)continue;
		swap(weight[row], weight[mx]);
		swap(nums[row], nums[mx]);
		sum += weight[row];
		for (int i = 1; i <= n; i++) {
			if (((nums[i] >> col) & 1) == 0 || i == row)continue;
			nums[i] ^= nums[row];
		}
		row++;

	}
	cout << sum << '\n';
}