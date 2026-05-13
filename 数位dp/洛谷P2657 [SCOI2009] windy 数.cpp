#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int  f(int num, int i, vector<vector<vector<int>>>&dp, int pre, int free, int offset) {
	if (i == 0)return 1;
	if (dp[i][pre][free] != -1)return dp[i][pre][free];
	int ans = 0;
	int cur = (num / offset) % 10;
	if (free == 0) {
		if (pre == 10) {
			ans += f(num, i - 1, dp, pre, 1, offset / 10);
			for (int j = 1;j < cur;j++) {
				ans += f(num, i - 1, dp, j, 1, offset / 10);
			}
			ans += f(num, i - 1, dp, cur, 0, offset / 10);
		}
		else {
			for (int j = 0;j <= 9;j++) {
				if (abs(j - pre) >= 2) {
					if (j < cur)ans += f(num, i - 1, dp, j, 1, offset / 10);
					else if (j == cur)ans += f(num, i - 1, dp, cur, 0, offset / 10);
				}

			}
		}
	}
	else {
		if (pre == 10) {
			ans += f(num, i - 1, dp, pre, 1, offset / 10);
			for (int j = 1;j <= 9;j++) {
				ans += f(num, i - 1, dp, j, 1, offset / 10);
			}
		}
		else {
			for (int j = 0;j <= 9;j++) {
				if (abs(j - pre) >= 2) {
					ans += f(num, i - 1, dp, j, 1, offset / 10);
				}
			}
		}

	}
	dp[i][pre][free] = ans;
	return ans;
}
int main() {
	int a, b;
	cin >> a >> b;
	int len = 0;
	int tmp = a - 1;
	while (tmp) {
		tmp /= 10;
		len++;
	}
	int offset = pow(10, len - 1);
	vector<vector<vector<int>>>dp(len + 1, vector<vector<int>>(11, vector<int>(2, -1)));
	int ans1 = f(a - 1, len, dp, 10, 0, offset);
	tmp = b;
	len = 0;
	while (tmp) {
		tmp /= 10;
		len++;
	}
	offset = pow(10, len - 1);
	dp.assign(len + 1, vector<vector<int>>(11, vector<int>(2, -1)));
	int ans2 = f(b, len, dp, 10, 0, offset);
	cout << ans2 - ans1 << endl;
}