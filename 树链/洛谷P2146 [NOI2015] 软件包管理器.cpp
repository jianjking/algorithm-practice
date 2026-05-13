#include<iostream>
#include<vector>
#include<climits>
using namespace std;
vector<int>son;
vector<int>sz;
vector<int>top;
vector<int>fa;
vector<int>dfn;
vector<int>seg;
vector<int>sum;
vector<int>reset;
vector<bool>update;
vector<vector<int>>graph;
int cnt = `;
void dfs1(int u, int v) {
	fa[u] = v;
	sz[u] = 1;
	for (auto& p : graph[u]) {
		if (p != v) {
			dfs1(p, u);
			sz[u] += sz[p];
			if (son[u] == 0 || sz[son[u]] < sz[p]) {
				son[u] = p;
			}
		}
	}
}
void dfs2(int u, int v) {
	dfn[u] = cnt;
	seg[u] = cnt++;
	top[u] = v;
	if (son[u] == 0)return;
	dfs2(son[u], v);
	for (auto& p : graph[u]) {
		if (p != fa[u] && p != son[u]) {
			dfs2(p, p);
		}
  }
}
void lazy(int l, int r, int w, int nums) {
	reset[nums] = w;
	update[nums] = true;
	sum[nums] = (r - l + 1) * w;
}
void down(int l, int r, int nums) {
	if (update[nums]) {
		int mid = l + (r - l) / 2;
		update[nums] = false;
		lazy(l, mid,reset[nums], 2 * nums);
		lazy(mid + 1, r, reset[nums], 2 * nums + 1);
	}
}
void up(int nums) {
	sum[nums] = sum[2 * nums] + sum[2 * nums + 1];
}
void updation(int x, int y, int l, int r, int w, int nums) {
	if (x <= l && y >= r) {
		lazy(l, r, w, nums);
		return;
	}
	else {
		down(l, r, nums);
		int mid = l + (r - l) / 2;
		if (x <= mid) {
			updation(x, y, l, mid, w, 2 * nums);
		}
		if (y > mid) {
			updation(x, y, mid + 1, r, w, 2 * nums + 1);
		}
		up(nums);
	}
}
int query(int x, int y, int l, int r, int nums) {
	if (x <= l && y >= r) {
		return sum[nums];
	}
	down(l, r, nums);
	int mid = l + (r - l) / 2;
	int ans = 0;
	if (x <= mid) {
		ans += query(x, y, l, mid, 2 * nums);
	}
	if (y > mid) {
		ans += query(x, y, mid + 1, r, 2 * nums + 1);
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	son.assign(n + 1, 0);
	sz.assign(n + 1, 0);
	fa.assign(n + 1, 0);
	dfn.assign(n + 1, 0);
	seg.assign(n + 1, 0);
	top.assign(n + 1, 0);
		sum.assign(4 * n +1, 0);
	reset.assign(4 * n + 1, 0);
	update.assign(4 * n + 1, false);
	graph.assign(n + 1, vector<int>(0));
	for (int i = 2; i <= n; i++) {
		int x;
		cin >> x;
		graph[x + 1].push_back(i);
	}
	dfs1(1, 1);
	dfs2(1, 1);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		string s;
		int x;
		cin >> s>>x;
		if (s == "install") {
			int ans = 0;
			while (top[x] != 1) {
				int sum1 = query(dfn[top[x]], dfn[x], 1, n, 1);
				updation(dfn[top[x]], dfn[x], 1, n, 1, 1);
				int sum2 = query(dfn[top[x]], dfn[x], 1, n, 1);
				ans += sum2 - sum1;
				x = fa[top[x]];
			}
			int sum1 = query(dfn[top[x]], dfn[x], 1, n, 1);
			updation(dfn[1], dfn[x], 1, n, 1, 1);
			int sum2 = query(dfn[top[x]], dfn[x], 1, n, 1);
			ans += sum2 - sum1;
			cout << ans << '\n';
		}
		else {
			int ans = 0;
			cout << query(dfn[x], dfn[x] + sz[x] - 1, 1, n, 1)<<'\n';
			updation(dfn[x], dfn[x] + sz[x] - 1, 1, n, 0, 1);
		}
	}
}
