#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n, x;
	cin >> n >> x;
	x *= 2;
	vector<ll>nums(n);
	for (int i = 0;i < n-1;i++) {
		cin >> nums[i];
	}
	nums[n - 1] = x;
	ll sum = 0;
	ll ans = 0;
	for (ll l = 0, r = 0;r < n;l++) {
		while (r < n && sum < x) {
			sum += nums[r];
			r++;
		}
		ans = max(ans, r - l);
		sum -= nums[l];
	}
	cout << ans << '\n';
}