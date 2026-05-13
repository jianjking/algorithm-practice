#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int power(ll m) {
	int p = 0;
	while (((long long)1 << p) <=( m >> 1)) {
		p++;
	}
	return p;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>>line(n, vector<ll>(3));
	for (int i = 0;i < n;i++) {
		cin >> line[i][1] >> line[i][2];
		if (line[i][2] < line[i][1])line[i][2] += m;
		line[i][0] = i;
	}
	line.reserve(2 * n);
	for (int i = 0;i < n;i++) {
		line.push_back({ i,line[i][1] + m,line[i][2] + m });
	}
	sort(line.begin(), line.end(), [&](auto a, auto b) {
		return a[1] < b[1];
		});
	int limit = power(m);
	vector<vector<int>>st(2*n, vector<int>(limit + 1, 0));
	for (int i = 0, j = 1;i < 2*n;i++) {
		while (j < 2 * n && line[j][1] <= line[i][2])j++;
		st[i][0] = j-1;
	}
	for (int i = 1;i <= limit;i++) {
		for (int j = 0;j < 2*n;j++) {
			st[j][i] = st[st[j][i - 1]][i - 1];
		}
	}
	vector<int>ans(n);
	
	for (int i = 0;i < n;i++) {
		ll j = i;
		ll tmp = line[i][1] + m;
		ll cnt = 0;
		for (int z = limit;z >= 0;z--) {
			if (tmp > line[st[j][z]][2]) {
				j = st[j][z];
				cnt += pow(2, z);
			}
		}
		ans[line[i][0]] = cnt + 2;
	}
	for (int i = 0;i < n;i++) {
		cout << ans[i] << " ";
	}
}