#include<iostream>
#include<vector>
using namespace std;
double INF = 1e-7;
int guess(vector<vector<double>>& nums) {
	int n = nums.size();
	int m = nums[0].size();
	for (int i = 1; i < n; i++) {
		int mx = i;
		for (int j = 1; j < n; j++) {
			if (j < i && fabs(nums[j][j]) >= INF) {
				continue;
			}
			if (fabs(nums[j][i]) > fabs(nums[mx][i]))mx = j;
		}
		swap(nums[mx], nums[i]);
		if (fabs(nums[i][i]) <= INF)continue;
		double x = nums[i][i];
		for (int j = i; j < m; j++) {
			nums[i][j] /= x;
		}
		for (int j = 1; j < n; j++) {
			if (j == i) continue;
			double tmp = nums[j][i] / nums[i][i];
			for (int z = i; z < m; z++) {
				nums[j][z] -= tmp * nums[i][z];
			}
		}
	}
	int mx = 0;
	int cnt = 0;
	int num;
	for (int i = 1; i < n; i++) {
		if (fabs(nums[i][i]) <= INF)return false;
		if (nums[i][m - 1] < 0 || nums[i][m - 1] != (int)nums[i][m - 1])return false;
		if (mx < nums[i][m - 1]) {
			mx = nums[i][m - 1];
			cnt = 1;
			num = i;
		}
		else if (mx == nums[i][m - 1])cnt++;
	}
	if (cnt > 1)return false;
	return num;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<vector<double>>data(n + 2, vector<double>(n + 2, 0));
	for (int i = 1; i <= n + 1; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int tmp;
			cin >> tmp;
			data[i][tmp]++;
		}
		int w;
		cin >> w;
		data[i][n + 1] = w;
	}
	int cnt = 0;
	int mx;
	for (int i = 1; i <= n + 1; i++) {
		vector<vector<double>>nums;
		for (int j = 0; j <= n + 1; j++) {
			if (j == i)continue;
			nums.push_back(data[j]);
		}
		int tmp = guess(nums);
		if (tmp) {
			mx = tmp;
			cnt++;
		}
	}
	if (cnt != 1) {
		cout << "illegal";
	}
	else {
		cout << mx << '\n';
	}
}