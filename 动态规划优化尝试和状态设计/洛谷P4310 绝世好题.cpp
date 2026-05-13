#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;
int main() {
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int>pre(32, 0);
	for (int i = 0;i < n;i++) {
		 int tmp;
		cin >> tmp;
		int cur = 1;
		for (int i = 31;i >= 0;i--) {
			if (((tmp >> i) & 1) == 1) {
				cur = max(cur, pre[i] + 1);
			}
	     }
		for (int i = 31;i >= 0;i--) {
			if (((tmp >> i) & 1 )== 1) {
				pre[i] = max(cur, pre[i]);
			}
		}
	}
	int ans = INT_MIN;
	for (auto& p : pre)ans = max(ans, p);
	cout << ans << '\n';
}