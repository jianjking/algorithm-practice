#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void add(int a, int b, vector<long long>&tree) {
	int n = tree.size();
	while (a <= n) {
		tree[a] += b;
		a += (a & -a);
	}
}
long long queriry(int a, vector<long long>& tree) {
	long long sum = 0;
	while (a > 0) {
		sum += tree[a];
		a -= a & (-a);
	}
	return sum;
}
int main() {
	int n;
	cin >> n;
	vector<long long>tree(n + 1, 0);
	vector<long long>num(n, 0);
	vector<long long>nums(n, 0);
	for (int i = 0;i < n;i++) {
		cin >> num[i];
	}
	nums = num;
	sort(nums.begin(), nums.end());
	auto p2=unique(nums.begin(), nums.end());
	nums.erase(p2, nums.end());
	for (int i = 0;i < n;i++) {
		auto p = lower_bound(nums.begin(), nums.end(), num[i]) - nums.begin() + 1;
		num[i] = p;
	}
	long long ans = 0;
	for (int i = n - 1;i >= 0;i--) {
		ans += queriry(num[i]-1, tree);
		add(num[i], 1, tree);
	}
	cout<<ans<<endl;
}