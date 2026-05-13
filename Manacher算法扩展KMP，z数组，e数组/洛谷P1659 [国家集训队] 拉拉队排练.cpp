#include<iostream>
#include<vector>
using namespace std;
const int mod = 19930726;
long long f(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1)res = (res * (long long)a) % mod;
		a = ((long long)a * a) % mod;
		b >>= 1;
	}
	return res;
}
int main() {
	long long m, k;
	cin >> m >> k;
	vector<int>arr(m + 1, 0);
	string tmp;
	cin >> tmp;
	string s = "#";
	for (auto p : tmp) {
		s += p;
		s += "#";
	}
	int n = s.size();
	vector<int>p(n, 0);
	for (int i = 0, r = 0, c = 0;i < n;i++) {
		int len = r > i ? min(r - i, p[2 * c - i]) : 1;
		while (i - len >= 0 && i + len < n && s[i - len] == s[i + len])len++;
		if (i + len > r) {
			r = i + len;
			c = i;
		}
		p[i] = len;

	}
	for (int i = 1;i < n;i++) {
		arr[p[i] - 1]++;
	}
	int ans = 1;
	long long sum = 0;
	for (int i = m % 2 == 0 ? m - 1 : m;i > 0 && k > 0;i -= 2) {

		sum += arr[i];
		int tmp = min(k, sum);
		ans = ((long long)ans * f(i, tmp)) % mod;
		k -= sum;

	}
	ans = k > 0 ? -1 : ans;
	cout << ans;
}