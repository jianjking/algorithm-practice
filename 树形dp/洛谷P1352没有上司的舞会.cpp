
#include<iostream>
#include<vector>
using namespace std;
void f(int root, vector<int>& yes, vector<int>& no, vector<int>& to, vector<int>& nxt, vector<int>& head1, vector<int>& happy) {
	no[root] = 0;
	yes[root] = happy[root];
	for (int i = head1[root];i > 0;i = nxt[i]) {
		f(to[i], yes, no, to, nxt, head1, happy);
		no[root] += max(no[to[i]], yes[to[i]]);
		yes[root] += no[to[i]];
	}
}
int main() {
	int n;
	cin >> n;
	vector<int>happy(n + 1);
	for (int i = 0;i < n;i++) {
		cin >> happy[i + 1];
	}
	vector<int>head1(n + 1, 0);
	vector<int>to(2 * n + 1, 0);
	vector<int>nxt(2 * n + 1, 0);
	int cnt = 1;
	int a, b;
	vector<bool>boss(n + 1, true);
	while (cin >> a >> b) {
		nxt[cnt] = head1[b];
		to[cnt] = a;
		head1[b] = cnt++;
		boss[a] = false;
	}
	int root;
	for (int i = 1;i <= n;i++) {
		if (boss[i])root = i;
	}
	vector<int>yes(n + 1, 0);
	vector<int>no(n + 1, 0);
	f(root, yes, no, to, nxt, head1, happy);
	cout << max(yes[root], no[root]) << endl;
}