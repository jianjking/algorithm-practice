#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
int f(string& s, int i, int pp, int p, int free, vector<vector<vector<vector<int>>>>&dp) {
	if (i == s.size())return 1;
	if (dp[i][pp][p][free] != -1)return dp[i][pp][p][free];
	int ans = 0;
	int cur = s[i] - '0';
	if (free == 0) {
		if (p == 10) {
			ans =(ans+ f(s, i + 1, pp, p, 1, dp))%mod;
			for (int j = 1;j < cur;j++)ans =(ans+ f(s, i + 1, p, j, 1, dp))%mod;
			ans =(ans+ f(s, i + 1, p, cur, 0, dp))%mod;
		}
		else {
			for (int j = 0;j < cur;j++) {
				if (j != pp && j != p) {
					ans =(ans+ f(s, i + 1, p, j, 1, dp))%mod;
				}
			}
			if (cur != pp && cur != p)ans =(ans+ f(s, i + 1, p, cur, 0, dp))%mod;
		}
	}
	else {
		if (p == 10) {
			ans =(ans+ f(s, i + 1, pp, p, 1, dp))%mod;
			for (int j = 1;j <= 9;j++) {
				ans = (ans + f(s, i + 1, p, j, 1, dp) )% mod;
			}
		}
		else {
			for (int j = 0;j <= 9;j++) {
				if (j != p && j != pp)ans = (ans + f(s, i + 1, p, j, 1, dp)) % mod;
			}
		}
	}
	dp[i][pp][p][free] = ans;
	return ans;
}
bool pan(string& s) {
	for (int pp = -2, p = -1, i = 0;i < s.size();pp++,p++,i++) {
		if (pp >= 0 && s[i] == s[pp])return true;
		if (p >= 0 && s[i] == s[p])return true;
	}
	return false;
}
int main() {
	string a, b;
	cin >> a >> b;
	long long n1 = a[0]-'0';
	for (int i = 1;i < a.size();i++) {
		n1 = (n1 * 10+a[i]-'0') % mod;
	}
	long long n2 = b[0]-'0';
	for (int i = 1;i < b.size();i++) {
		n2 = (n2 * 10 + b[i]-'0') % mod;
	}

	vector<vector<vector<vector<int>>>>dp(a.size(), vector<vector<vector<int>>>(11, vector<vector<int>>(11, vector<int>(11, -1))));
	int ans1=f(a,0, 10, 10, 0,dp);
	dp.assign(b.size(), vector<vector<vector<int>>>(11, vector<vector<int>>(11, vector<int>(11, -1))));
	int ans2 = f(b, 0, 10, 10, 0, dp);
	int ans = (n2-ans2 -n1+ ans1 + mod) % mod;
	if (pan(a))ans = (ans + 1) % mod;
	cout<<ans<<endl;
}

