#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
unordered_set<int>cnt;
vector<bool>vis;
vector<long long>num;
void lazy(int i, int v) {
	num[i] = v;
	vis[i] = true;
}
void down(int i) {
	lazy(2 * i, num[i]);
	lazy(2 * i + 1, num[i]);
	vis[i] = false;
}
void update(int a, int b, int c, int d, int i,int p) {
	if (a <= c && b >= d) {
		lazy(i, p);
	}
	else {
		if (vis[i]) {
			down(i);
		}
		int mid = c + (d - c) / 2;
		if(mid>=a)update(a, b, c, mid, 2 * i, p);
		if (b > mid)update(a, b, mid + 1, d, 2 * i + 1, p);
	}
}
void query(int a,int b,int l, int r, int i) {
	if (l == r) { if (num[i] != 0)cnt.insert(num[i]); }
	else {
		if (vis[i])down(i);
		int mid = l + (r - l) / 2;
		if (mid >= a)query(a, b, l, mid, 2 * i);
		if (b > mid)query(a, b, mid + 1, r, 2 * i + 1);
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	vector<vector<long long>>res(m+1,vector<long long>(2));
	vector<long long>nums;
	nums.reserve(2 * m);
	for (int i = 1;i <= m;i++) {
		int a, b;
		cin >> a >> b;
		res[i][0]=a;
		nums.push_back(a);
		nums.push_back(b);
		res[i][1] = b;
	}
	sort(nums.begin(), nums.end());
	auto p2 = unique(nums.begin(), nums.end());
	nums.erase(p2, nums.end());
	vector<long long>tmp;
	tmp.reserve(4 * m);
	for (int i = 1;i < nums.size();i++) {
		tmp.push_back(nums[i - 1]);
		if (nums[i] - nums[i - 1] > 1)tmp.push_back(nums[i - 1] + 1);
	}
	vis.assign(4 * tmp.size()+1, false);
	num.assign(4 * tmp.size()+1, 0);
	tmp.push_back(nums[nums.size() - 1]);
	n = upper_bound(tmp.begin(), tmp.end(), n) - tmp.begin() ;
	for (int i = 1;i <= m;i++) {
		int a = lower_bound(tmp.begin(), tmp.end(), res[i][0])-tmp.begin()+1;
		int b = lower_bound(tmp.begin(), tmp.end(), res[i][1]) - tmp.begin()+1;
		update(a, b, 1, tmp.size(), 1,i);
	}
	query(1, n, 1, tmp.size(), 1);
	cout << cnt.size() << endl;;
}