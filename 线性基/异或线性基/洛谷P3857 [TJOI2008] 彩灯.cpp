#include<iostream>
#include<vector>
using namespace std;
int kuaisu(int a, int b) {
	long long ans = 1;
	while (b > 0) {
		if (b & 1) {
			ans = (ans * a) % 2008;
		}
		a = (a * a) % 2008;
		b >>= 1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<long long>nums(m + 1, 0);
	for (int i = 1; i <= m; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			long long sign = s[j] == 'O' ? 1 : 0;
			nums[i] |= sign << j;
		}
	}
	int row = 1;
	for (int col = n - 1; col >= 0; col--) {
		int mx = -1;
		for (int r = row; r <= m; r++) {
			if (((nums[r] >> col) & 1) == 1) {
				mx = r;
				break;
			}
		}
		if (mx == -1)continue;
		swap(nums[mx], nums[row]);
		for (int i = 1; i <= m; i++) {
			if (((nums[i] >> col) & 1) == 0 || i == row)continue;
			nums[i] ^= nums[row];
		}
		row++;
	}
	long long ans = kuaisu(2, row - 1);

	cout << ans << '\n';
}