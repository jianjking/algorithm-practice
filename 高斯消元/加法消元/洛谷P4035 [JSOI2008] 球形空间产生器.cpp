#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
const double INF = 1e-7;
void guess(vector<vector<double>>& nums) {
	int n = nums.size();
	int m = nums[0].size();
	for (int i = 1; i < n; i++) {
		int mx = i;
		for (int j = 1; j < n; j++) {
			if (j < i && fabs(nums[j][j]) >= INF) {
				continue;
			}
			if (fabs(nums[mx][i]) < fabs(nums[j][i])) {
				mx = j;
			}
		}
		swap(nums[i], nums[mx]);
		if (fabs(nums[i][i]) <= INF)continue;
		double x = nums[i][i];
		for (int j = i; j < m; j++) {
			nums[i][j] /= x;
		}
		for (int j = 1; j < n; j++) {
			if (j == i)continue;
			double x = nums[j][i] / nums[i][i];
			for (int z = i; z < m; z++) {
				nums[j][z] -= x * nums[i][z];
			}
		}
	}
}
int main() {
	int n;
	cin >> n;
	vector<vector<double>>nums(n + 1, vector<double>(n + 2, 0));
	vector<double>arr(n + 1);
	double sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		sum += -arr[i] * arr[i];
		arr[i] *= -2;
	}

	for (int i = 1; i <= n; i++) {
		double tmp = 0;
		for (int j = 1; j <= n; j++) {
			double ch;
			cin >> ch;
			tmp += ch * ch;
			nums[i][j] += arr[j] + ch * 2;
		}
		nums[i][n + 1] = tmp + sum;
	}
	guess(nums);
	for (int i = 1; i <= n; i++) {
		cout << fixed << setprecision(3) << nums[i][n + 1] << " ";
	}
}