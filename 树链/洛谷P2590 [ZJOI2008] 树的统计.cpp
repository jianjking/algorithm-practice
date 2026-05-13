#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int n, q;

vector<vector<int>> graph;
vector<int> fa, dep, top, dfn, seg, son, sz;
vector<int> weight;

int timer_ = 1;

// 线段树：维护 DFS 序上的点权（支持点改、区间和、区间 max）
struct SegTree {
    int N;
    vector<long long> sum; // 区间和
    vector<int> mx;        // 区间最大

    SegTree() {}
    SegTree(int n) { init(n); }
    void init(int n) {
        N = n;
        sum.assign(4 * N + 5, 0);
        mx.assign(4 * N + 5, INT_MIN);
    }
    inline void up(int p) {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
    void build(int p, int l, int r) {
        if (l == r) {
            int u = seg[l];                // seg[l] 是 DFS 序位置 l 对应的原节点
            sum[p] = (long long)weight[u];
            mx[p] = weight[u];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        up(p);
    }
    // 单点修改：把 pos 的值改为 val
    void update(int p, int l, int r, int pos, int val) {
        if (l == r) {
            sum[p] = val;
            mx[p] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (pos <= m) update(p << 1, l, m, pos, val);
        else          update(p << 1 | 1, m + 1, r, pos, val);
        up(p);
    }
    // 区间和
    long long qsum(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return sum[p];
        int m = (l + r) >> 1;
        long long ans = 0;
        if (L <= m) ans += qsum(p << 1, l, m, L, R);
        if (R > m) ans += qsum(p << 1 | 1, m + 1, r, L, R);
        return ans;
    }
    // 区间 max
    int qmax(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return mx[p];
        int m = (l + r) >> 1;
        int ans = INT_MIN;
        if (L <= m) ans = max(ans, qmax(p << 1, l, m, L, R));
        if (R > m) ans = max(ans, qmax(p << 1 | 1, m + 1, r, L, R));
        return ans;
    }
} segt;

// ====== HLD ======
void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = (f == u ? 1 : dep[f] + 1); // 根的深度设为 1
    sz[u] = 1;
    son[u] = 0;
    for (int v : graph[u]) if (v != f) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[son[u]] < sz[v]) son[u] = v; // 记录重儿子
    }
}

void dfs2(int u, int topu) {
    top[u] = topu;
    dfn[u] = timer_;
    seg[timer_] = u;
    timer_++;
    if (son[u]) {
        dfs2(son[u], topu); // 先沿重链
        for (int v : graph[u]) {
            if (v != fa[u] && v != son[u]) {
                dfs2(v, v); // 轻边开新链
            }
        }
    }
}

// 路径上区间和
long long path_sum(int u, int v) {
    long long ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            ans += segt.qsum(1, 1, n, dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        else {
            ans += segt.qsum(1, 1, n, dfn[top[v]], dfn[v]);
            v = fa[top[v]];
        }
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    ans += segt.qsum(1, 1, n, dfn[u], dfn[v]);
    return ans;
}

// 路径上区间最大
int path_max(int u, int v) {
    int ans = INT_MIN;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            ans = max(ans, segt.qmax(1, 1, n, dfn[top[u]], dfn[u]));
            u = fa[top[u]];
        }
        else {
            ans = max(ans, segt.qmax(1, 1, n, dfn[top[v]], dfn[v]));
            v = fa[top[v]];
        }
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    ans = max(ans, segt.qmax(1, 1, n, dfn[u], dfn[v]));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    graph.assign(n + 1, {});
    fa.assign(n + 1, 0);
    dep.assign(n + 1, 0);
    top.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    seg.assign(n + 1, 0);
    son.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    weight.assign(n + 1, 0);

    // 读边
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 根设为 1
    dfs1(1, 1);
    dfs2(1, 1);

    // 读权（1..n）
    for (int i = 1; i <= n; i++) cin >> weight[i];

    // 建树（按 DFS 序）
    segt.init(n);
    segt.build(1, 1, n);

    // 读操作数
    cin >> q;
    while (q--) {
        string op; int u, v;
        cin >> op >> u >> v;
        if (op == "CHANGE") {
            // 点 u 的权值改为 v
            segt.update(1, 1, n, dfn[u], v);
        }
        else if (op == "QMAX") {
            cout << path_max(u, v) << '\n';
        }
        else if (op == "QSUM") {
            cout << path_sum(u, v) << '\n';
        }
        else {
            // 可选：容错
            // cerr << "Unknown op: " << op << "\n";
        }
    }
    return 0;
}
