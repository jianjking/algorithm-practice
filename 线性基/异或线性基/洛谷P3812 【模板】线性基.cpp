#include<iostream>
#include<vector>
using namespace std;
int main() {
	int limit = 51;
	int n;
	cin >> n;
	vector<long long>nums(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	int row = 1;
	for (int col = 50; col >= 0 && row <= n; col--) {
		int mx = -1;
		for (int r = row; r <= n; r++) {
			if (((nums[r] >> col) & 1) == 1) {
				mx = r;
				break;
			}
		}
		if (mx == -1)continue;
		swap(nums[mx], nums[row]);
		for (int i = 1; i <= n; i++) {
			if (((nums[i] >> col) & 1) == 0 || i == row)continue;
			nums[i] ^= nums[row];
		}
		row++;
	}
	long long ans = 0;
	for (int i = 1; i < row; i++) {
		ans ^= nums[i];
	}
	cout << ans << '\n';
}