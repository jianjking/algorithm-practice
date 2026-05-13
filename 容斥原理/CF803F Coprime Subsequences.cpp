#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
int main() {
	int n;
	cin >> n;
	vector<int>dp(100001, 0);
	int mx = INT_MIN;
		for (int i = 0;i < n;i++) {
			int a;
			cin >> a;
			dp[a]++;
			mx = max(mx, a);
	}
		vector<int>ans(mx+1, 0);
		vector<int>cnt(n+1,1);
		for (int i = 1;i <= n;i++) {
			cnt[i] = (2LL * cnt[i - 1]) % mod;
		}
		for (int i = mx;i > 0;i--) {
			int cn = dp[i];
			int cn1 = 0;
			for (int j = 2 * i;j <= mx;j += i) { 
				cn += dp[j];
				cn1 =(cn1+ ans[j])%mod;
			}
			ans[i] = (cnt[cn] - 1 - cn1+mod)%mod;
		}
		cout << ans[1] << endl;
}
