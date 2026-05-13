#include<iostream>
#include<vector>
using namespace std;
vector<int> up(const vector<int>& l, const vector<int>& r) {
	vector<int>tmp = l;
	for (int i = 31; i >= 0; i--) {
		int v = r[i];
		for (int i = 31; i >= 0; i--) {
			if (((v >> i) & 1) == 1) {
				if (tmp[i] == 0) {
					tmp[i] = v;
					break;
				}
				else {
					v ^= tmp[i];
				}
			}
		}
	}
	return tmp;
}
void add(int target, int l, int r, vector<vector<int>>& nums, int v, int num) {
	if (l == r) {
		for (int i = 31; i >= 0; i--) {
			if (((v >> i) & 1) == 1) {
				if (nums[num][i] == 0) {
					nums[num][i] = v;
					break;
				}
				else v ^= nums[num][i];
			}
		}
		return;
	}
	else {
		int mid = l + (r - l) / 2;
		if (target <= mid)add(target, l, mid, nums, v, 2 * num);
		else add(target, mid + 1, r, nums, v, 2 * num + 1);
		nums[num] = up(nums[2 * num], nums[2 * num + 1]);
	}
}
vector<int>query(int x, int y, int l, int r, vector<vector<int>>& nums, int num) {
	if (x <= l && y >= r) {
		return nums[num];
	}
	int mid = l + (r - l) / 2;
	if (y <= mid) {
		return query(x, y, l, mid, nums, 2 * num);
	}
	else if (x > mid) {
		return query(x, y, mid + 1, r, nums, 2 * num + 1);
	}
	else {
		vector<int>l1 = query(x, y, l, mid, nums, 2 * num);
		vector<int>r1 = query(x, y, mid + 1, r, nums, 2 * num + 1);
		return up(l1, r1);
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>>nums(4 * m + 1, vector<int>(32, 0));
	for (int i = 0; i < n; i++) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1)add(x, 1, m, nums, y, 1);
		else {
			vector<int>ans = query(x, y, 1, m, nums, 1);
			int sum = 0;
			for (int i = 31; i >= 0; i--) {
				sum = max(sum, sum ^ ans[i]);
			}
			cout << sum << '\n';
		}
	}
}