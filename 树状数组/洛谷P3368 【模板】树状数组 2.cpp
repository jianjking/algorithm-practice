#include<iostream>
#include<vector>
using namespace std;
void add(int a, int b, vector<int>& tree) {
	int n = tree.size();
	while(a<n){
		tree[a] += b;
		a += (a & (-a));
	}
}
int queriry(int a, vector<int>& tree) {
	int ans = 0;
	while (a > 0) {
		ans += tree[a];
		a -= (a & (-a));
	}
	return ans;
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<int>tree(n + 2, 0);
	for (int i = 1;i <= n;i++) {
		int tmp;
		cin >> tmp;
		add(i, tmp, tree);
		add(i + 1, -tmp, tree);
	}
	for (int i = 0;i < m;i++) {
		int a;
		cin >> a;
		if (a == 1) {
			int c, d, e;
			cin >> c >> d >> e;
			add(c, e, tree);
			add(d + 1, -e, tree);
		}
		else {
			int c;
			cin >> c;
			cout << queriry(c, tree)<<endl;
		}
	}
}