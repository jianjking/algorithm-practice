#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int lcolor, rcolor, sum; // 左端颜色、右端颜色、颜色段数
    Node(int a = 0, int b = 0, int c = 0) :lcolor(a), rcolor(b), sum(c) {}
};

int n, m;
vector<int> sz, son, dep, fa, dfn, seg, top;
vector<int> lcolor, rcolor, sumv, resetv, weight;
vector<bool> updatev;
vector<vector<int>> g;
int timer_ = 1;

// --- HLD: dfs1/dfs2 ---
void dfs1(int u, int p) {
    fa[u] = p; dep[u] = dep[p] + 1; sz[u] = 1;
    for (int v : g[u]) if (v != p) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
    }
}
void dfs2(int u, int tp) {
    dfn[u] = timer_;
    seg[timer_++] = u;
    top[u] = tp;
    if (son[u]) {
        dfs2(son[u], tp);
        for (int v : g[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
    }
}

// --- segtree 基本 ---
inline Node mergeNode(const Node& L, const Node& R) {
    if (L.sum == 0) return R;
    if (R.sum == 0) return L;
    Node res;
    res.lcolor = L.lcolor;
    res.rcolor = R.rcolor;
    res.sum = L.sum + R.sum - (L.rcolor == R.lcolor);
    return res;
}
inline Node reverseNode(Node t) { swap(t.lcolor, t.rcolor); return t; }

void up(int idx) {
    lcolor[idx] = lcolor[idx << 1];
    rcolor[idx] = rcolor[idx << 1 | 1];
    sumv[idx] = sumv[idx << 1] + sumv[idx << 1 | 1] - (rcolor[idx << 1] == lcolor[idx << 1 | 1]);
}
void apply_lazy(int idx, int c) {
    updatev[idx] = true; resetv[idx] = c;
    lcolor[idx] = rcolor[idx] = c;
    sumv[idx] = 1;
}
void down(int idx) {
    if (updatev[idx]) {
        updatev[idx] = false;
        apply_lazy(idx << 1, resetv[idx]);
        apply_lazy(idx << 1 | 1, resetv[idx]);
    }
}
void build(int l, int r, int idx) {
    if (l == r) {
        int u = seg[l];
        lcolor[idx] = rcolor[idx] = weight[u];
        sumv[idx] = 1;              // 叶子就是一个颜色段
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, idx << 1);
    build(mid + 1, r, idx << 1 | 1);
    up(idx);
}
void updation(int L, int R, int l, int r, int c, int idx) {
    if (L <= l && r <= R) { apply_lazy(idx, c); return; }
    down(idx);
    int mid = (l + r) >> 1;
    if (L <= mid) updation(L, R, l, mid, c, idx << 1);
    if (R > mid) updation(L, R, mid + 1, r, c, idx << 1 | 1);
    up(idx);
}
Node query(int L, int R, int l, int r, int idx) {
    if (L <= l && r <= R) return Node(lcolor[idx], rcolor[idx], sumv[idx]);
    down(idx);
    int mid = (l + r) >> 1;
    if (R <= mid) return query(L, R, l, mid, idx << 1);
    if (L > mid) return query(L, R, mid + 1, r, idx << 1 | 1);
    Node A = query(L, mid, l, mid, idx << 1);
    Node B = query(mid + 1, R, mid + 1, r, idx << 1 | 1);
    return mergeNode(A, B);
}

// --- HLD 路径操作 ---
void path_update(int a, int b, int c) {
    while (top[a] != top[b]) {
        if (dep[top[a]] >= dep[top[b]]) {
            updation(dfn[top[a]], dfn[a], 1, n, c, 1);
            a = fa[top[a]];
        }
        else {
            updation(dfn[top[b]], dfn[b], 1, n, c, 1);
            b = fa[top[b]];
        }
    }
    int L = dfn[a], R = dfn[b];
    if (L > R) swap(L, R);
    updation(L, R, 1, n, c, 1);
}
int path_query(int a, int b) {
    Node leftPart, rightPart;
    while (top[a] != top[b]) {
        if (dep[top[a]] >= dep[top[b]]) {
            // 取 top[a]→a，路径方向是 a→top[a]，需反转
            Node cur = query(dfn[top[a]], dfn[a], 1, n, 1);
            cur = reverseNode(cur);
            leftPart = mergeNode(leftPart, cur);
            a = fa[top[a]];
        }
        else {
            // 取 top[b]→b，方向与最终一致，拼到右侧前面
            Node cur = query(dfn[top[b]], dfn[b], 1, n, 1);
            rightPart = mergeNode(cur, rightPart);
            b = fa[top[b]];
        }
    }
    if (dfn[a] >= dfn[b]) {
        // 中段 b→a，需要反转成 a→b
        Node mid = query(dfn[b], dfn[a], 1, n, 1);
        mid = reverseNode(mid);
        Node all = mergeNode(leftPart, mergeNode(mid, rightPart));
        return all.sum;
    }
    else {
        Node mid = query(dfn[a], dfn[b], 1, n, 1);
        Node all = mergeNode(leftPart, mergeNode(mid, rightPart));
        return all.sum;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    g.assign(n + 1, {});
    sz.assign(n + 1, 0);
    son.assign(n + 1, 0);
    dep.assign(n + 1, 0);
    fa.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    seg.assign(n + 1, 0);
    top.assign(n + 1, 0);
    weight.assign(n + 1, 0);

    lcolor.assign(4 * n + 5, 0);
    rcolor.assign(4 * n + 5, 0);
    sumv.assign(4 * n + 5, 0);
    resetv.assign(4 * n + 5, 0);
    updatev.assign(4 * n + 5, false);

    for (int i = 1; i <= n; i++) cin >> weight[i];
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dep[0] = 0;
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);

    for (int i = 0; i < m; i++) {
        char op; cin >> op;
        if (op == 'C') {
            int x, y, w; cin >> x >> y >> w;
            path_update(x, y, w);
        }
        else { // 'Q'
            int a, b; cin >> a >> b;
            cout << path_query(a, b) << "\n";
        }
    }
    return 0;
}
}