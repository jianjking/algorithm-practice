#include<iostream>
#include<vector>
#include<unordered_map>
#include<stack>
#include<unordered_set>
#include<set>
using namespace std;
int mod;
using ll = long long;
vector<int>weight;
vector<vector<int>>graph;
vector<int>sz;
vector<ll>sum;
vector<int>sun;
vector<int>add;
vector<int>dfn;
vector<int>seg;
vector<int>fa;
vector<int>dep;
vector<int>top;
int cnt = 1;
void dfs1(int son, int parent) {
	sz[son] = 1;
	dep[son] = dep[parent] + 1;
	fa[son] = parent;
	for (auto& p : graph[son]) {
		if (p != parent) {
			dfs1(p, son);
			if (sun[son] == 0 || sz[sun[son]] < sz[p]) {
				sun[son] = p;
			}
			sz[son] += sz[p];
		}
	}

}
void dfs2(int u, int v) {
	top[u] = v;
	dfn[u] = cnt;
	seg[cnt++] = u;
	if (sun[u] == 0)return;
	dfs2(sun[u], v);
	for (auto& p : graph[u]) {
		if (p != fa[u] && p != sun[u]) {
			dfs2(p, p);
		}
	}
}
void lazy(int l, int r, int w, int nums) {
	add[nums] = (add[nums] + w) % mod;                        // ✅ 懒标记也始终模掉
	sum[nums] = (sum[nums] + (1LL * (r - l + 1) * w) % mod) % mod; // ✅ 乘法用 1LL
}



void down(int l, int r, int nums) {
	if (add[nums] != 0) {
		int w = add[nums];
		add[nums] = 0;
		int mid = l + (r - l) / 2;
		lazy(l, mid, w, 2 * nums);
		lazy(mid + 1, r, w, 2 * nums + 1);
	}
}
void up(int nums) {
	sum[nums] = (sum[nums * 2] + sum[2 * nums + 1]) % mod;
}
void addtion(int x, int y, int l, int r, int w, int nums) {
	if (x <= l && y >= r) {
		lazy(l, r, w, nums);
		return;
	}
	else {
		down(l, r, nums);
		int mid = l + (r - l) / 2;
		if (x <= mid) {
			addtion(x, y, l, mid, w, 2 * nums);
		}
		if (y > mid) {
			addtion(x, y, mid + 1, r, w, 2 * nums + 1);
		}
		up(nums);
	}
}
long long query(int x, int y, int l, int r, int nums) {
	if (x <= l && y >= r)return sum[nums];
	down(l, r, nums);
	int mid = l + (r - l) / 2;
	long long ans = 0;
	if (x <= mid) {
		ans = (ans + query(x, y, l, mid, 2 * nums)) % mod;
	}
	if (y > mid) {
		ans = (ans + query(x, y, mid + 1, r, 2 * nums + 1)) % mod;
	}
	return ans;
}
void build(int l, int r, int nums) {
	if (l == r) {
		sum[nums] = weight[seg[l]] % mod;
		add[nums] = 0;
		return;
	}
	int mid = l + (r - l) / 2;
	build(l, mid, 2 * nums);
	build(mid + 1, r, 2 * nums + 1);
	up(nums);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, root;
	cin >> n >> m >> root >> mod;
	weight.assign(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> weight[i];
	}
	sz.assign(n + 1, 0);
	sum.assign(4 * n + 1, 0);
	add.assign(4 * n + 1, 0);
	seg.assign(n + 1, 0);
	dfn.assign(n + 1, 0);
	sun.assign(n + 1, 0);
	fa.assign(n + 1, 0);
	dep.assign(n + 1, 0);
	graph.assign(n + 1, vector<int>(0));
	top.assign(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	dfs1(root, root);
	dfs2(root, root);
	build(1, n, 1);
	for (int i = 0; i < m; i++) {
		int k;
		cin >> k;
		if (k == 1) {
			int x, y, w;
			cin >> x >> y >> w;
			while (top[x] != top[y]) {
				int x1 = top[x];
				int y1 = top[y];
				if (dep[x1] < dep[y1]) {
					addtion(dfn[y1], dfn[y], 1, n, w, 1);
					y = fa[y1];
				}
				else {
					addtion(dfn[x1], dfn[x], 1, n, w, 1);
					x = fa[x1];
				}
			}
			addtion(min(dfn[x], dfn[y]), max(dfn[y], dfn[x]), 1, n, w, 1);
		}
		else if (k == 2) {
			int x, y;
			cin >> x >> y;
			long long ans = 0;
			while (top[x] != top[y]) {
				int x1 = top[x];
				int y1 = top[y];
				if (dep[x1] < dep[y1]) {
					ans = (ans + query(dfn[y1], dfn[y], 1, n, 1)) % mod;
					y = fa[y1];
				}
				else {
					ans = (ans + query(dfn[x1], dfn[x], 1, n, 1)) % mod;
					x = fa[x1];
				}
			}
			ans = (ans + query(min(dfn[x], dfn[y]), max(dfn[y], dfn[x]), 1, n, 1)) % mod;
			cout << ans << '\n';

		}
		else if (k == 3) {
			int x, w;
			cin >> x >> w;
			int y = dfn[x] + sz[x] - 1;
			addtion(dfn[x], y, 1, n, w, 1);
		}
		else {
			int x;
			cin >> x;
			int y = dfn[x] + sz[x] - 1;
			cout << query(dfn[x], y, 1, n, 1) << '\n';
		}
	}
}