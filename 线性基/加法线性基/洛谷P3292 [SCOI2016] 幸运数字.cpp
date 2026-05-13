#include<iostream>
#include<vector>
using namespace std;
static const int MAXB = 60;
void insert(long long v, int dep, vector<pair<long long, int>>& base) {
    pair<long long, int> tmp = { v, dep };
    for (int i = MAXB; i >= 0; --i) {
        if (((tmp.first >> i) & 1LL) == 0) continue;
        if (base[i].first == 0) {            // 空位，直接放
            base[i] = tmp;
            return;
        }
        else {
            // FIX: 比较“深度”而不是跟数值比；并且应保留更深的主元
            if (base[i].second < tmp.second) // 保留更深
                swap(tmp, base[i]);
            tmp.first ^= base[i].first;      // 消去当前位
        }
    }
}

void dfs(int u, int fa,
    vector<vector<int>>& st,
    vector<vector<pair<long long, int>>>& bases,
    vector<vector<int>>& g,
    vector<long long>& w,
    vector<int>& dep) {
    st[u][0] = fa;
    dep[u] = dep[fa] + 1;
    bases[u] = bases[fa];
    insert(w[u], dep[u], bases[u]);
    for (int v : g[u]) if (v != fa) dfs(v, u, st, bases, g, w, dep);
}

int lca(int x, int y, const vector<vector<int>>& st, const vector<int>& dep) {
    int LOG = (int)st[0].size();        // FIX: 用列数（层数）
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = LOG - 1; i >= 0; --i)  // FIX: 循环上界
        if (st[x][i] && dep[st[x][i]] >= dep[y]) x = st[x][i];
    if (x == y) return x;
    for (int i = LOG - 1; i >= 0; --i)
        if (st[x][i] != st[y][i]) { x = st[x][i]; y = st[y][i]; }
    return st[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> w(n + 1);
    for (int i = 1; i <= n; ++i) cin >> w[i];

    // 计算倍增层数
    int LOG = 0, t = n;
    while (t) { t >>= 1; ++LOG; }

    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> st(n + 1, vector<int>(LOG, 0));
    vector<vector<pair<long long, int>>> bases(n + 1, vector<pair<long long, int>>(MAXB + 1, { 0, 0 }));
    vector<int> dep(n + 1, 0);

    dfs(1, 0, st, bases, g, w, dep);

    // 倍增转移
    for (int j = 1; j < LOG; ++j) {
        for (int v = 1; v <= n; ++v) {
            int mid = st[v][j - 1];
            if (mid) st[v][j] = st[mid][j - 1];   // FIX: st[v][j]，不是 st[i][i]
        }
    }

    while (m--) {
        int x, y; cin >> x >> y;
        int p = lca(x, y, st, dep);

        // ans 是当前可用的线性基（只存主元向量）
        vector<long long> ans(MAXB + 1, 0);

        // 1) 先灌入 x 的主元：时间戳 >= depth[LCA]
        for (int i = MAXB; i >= 0; --i) {
            if (bases[x][i].first && bases[x][i].second >= dep[p]) {
                ans[i] = bases[x][i].first;
            }
        }

        // 2) 再灌入 y 的主元：时间戳 > depth[LCA]（避免 LCA 重复）
        for (int i = MAXB; i >= 0; --i) {
            if (bases[y][i].first && bases[y][i].second > dep[p]) { // FIX: 严格大于
                long long v = bases[y][i].first;
                for (int b = MAXB; b >= 0; --b) {
                    if (((v >> b) & 1LL) == 0) continue;
                    if (ans[b] == 0) { ans[b] = v; break; }
                    v ^= ans[b];
                }
            }
        }

        // 3) 求最大异或
        long long best = 0;
        for (int i = MAXB; i >= 0; --i)        // FIX: 60..0
            best = max(best, best ^ ans[i]);

        cout << best << '\n';
    }
    return 0;
}
