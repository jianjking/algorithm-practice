#include<iostream>
#include<vector>
using namespace std;
int main() {
	string s1,s2;
	cin >> s1 >> s2;
	int n = s2.size();
	vector<pair<char,int>>stack(s1.size());
	int cnt = 0;
	vector<int>next(n, -1);
	next[0] = 1;
	int i = 2;
	int cn = 0;
	while (i < n) {
		if (s2[i - 1] == s2[cn]) {
			next[i++] = ++cn;
		}
		else if (cn == 0) {
			next[i++] = 0;
		}
		else {
			cn = next[cn];
		}
	}
	int x = 0;
	int m = s1.size();
	int y = 0;
	while (x < m) {
		if (s1[x] == s2[y]) {
			x++;
			y++;
			stack[cnt++] = { s1[x - 1],y-1 };
		}
		else if(y==0){
			x++;
			stack[cnt++] = { s1[x - 1],-1 };
		}
		else {
			y = next[y];
		}
		if (y == n) {
			cnt -= n;
			y = cnt == 0 ? 0 : stack[cnt - 1].second + 1;
		}
	}
	string ans;
	for (int i = 0;i < cnt;i++) {
		ans += stack[i].first;
	}
	cout << ans << endl;
}