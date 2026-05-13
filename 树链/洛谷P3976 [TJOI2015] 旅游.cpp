#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct node {
    int lmax; // 路径方向“左到右”的最大 A[j]-A[i]
    int rmax; // 路径方向“左到右”的最大 A[i]-A[j]
    int mx;   // 区间最大值
    int mn;   // 区间最小值
    int add;  // 区间加懒标记
    node(int l = INT_MIN, int r = INT_MIN, int x = INT_MIN, int y = INT_MAX, int z = 0)
        : lmax(l), rmax(r), mx(x), mn(y), add(z) {
    }
};

vector<int> fa, sz, top, son, dfn, seg, dep, arr;
vector<vector<int>> graph;
vector<node> sumv;
int n, q, timercnt = 1;

void dfs1(int u, int p) {
    fa[u] = p;
    sz[u] = 1;
    dep[u] = dep[p] + 1;
    for (int v : graph[u]) if (v != p) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
    }
}
void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = timercnt;
    seg[timercnt++] = u;
    if (!son[u]) return;
    dfs2(son[u], tp);
    for (int v : graph[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
}

// 合并两个节点（左段在前，右段在后）
inline node mergeNode(const node& L, const node& R) {
    if (L.mx == INT_MIN) return R; // 左空
    if (R.mx == INT_MIN) return L; // 右空
    node t;
    t.lmax = max(L.lmax, max(R.lmax, R.mx - L.mn));
    t.rmax = max(L.rmax, max(R.rmax, L.mx - R.mn));
    t.mx = max(L.mx, R.mx);
    t.mn = min(L.mn, R.mn);
    t.add = 0; // 父节点不保留聚合懒值
    return t;
}

// 反转方向（把“左到右”的统计翻转）：lmax/rmax 互换，mx/mn 不变
inline node rev(node t) { swap(t.lmax, t.rmax); return t; }

// segtree
inline void apply_add(int idx, int v) {
    sumv[idx].mx = (sumv[idx].mx == INT_MIN ? INT_MIN : sumv[idx].mx + v);
    sumv[idx].mn = (sumv[idx].mn == INT_MAX ? INT_MAX : sumv[idx].mn + v);
    sumv[idx].add += v;
    // 注意：lmax/rmax 不随整体平移改变，无需改动
}
inline void push_down(int idx) {
    if (sumv[idx].add != 0) {
        int v = sumv[idx].add;
        sumv[idx].add = 0;
        apply_add(idx << 1, v);
        apply_add(idx << 1 | 1, v);
    }
}
void build(int l, int r, int idx) {
    if (l == r) {
        int u = seg[l];
        sumv[idx].mx = arr[u];
        sumv[idx].mn = arr[u];
        sumv[idx].lmax = 0;    // 单点：A[j]-A[i] 最大为 0（取 i=j）
        sumv[idx].rmax = 0;    // 同理
        sumv[idx].add = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, idx << 1);
    build(mid + 1, r, idx << 1 | 1);
    sumv[idx] = mergeNode(sumv[idx << 1], sumv[idx << 1 | 1]);
}
void range_add(int L, int R, int l, int r, int idx, int v) {
    if (L <= l && r <= R) { apply_add(idx, v); return; }
    push_down(idx); // ★ 你原来少了这句
    int mid = (l + r) >> 1;
    if (L <= mid) range_add(L, R, l, mid, idx << 1, v);
    if (R > mid) range_add(L, R, mid + 1, r, idx << 1 | 1, v);
    sumv[idx] = mergeNode(sumv[idx << 1], sumv[idx << 1 | 1]);
}
node range_query(int L, int R, int l, int r, int idx) {
    if (L <= l && r <= R) return sumv[idx];
    push_down(idx);
    int mid = (l + r) >> 1;
    if (R <= mid) return range_query(L, R, l, mid, idx << 1);
    if (L > mid) return range_query(L, R, mid + 1, r, idx << 1 | 1);
    node A = range_query(L, mid, l, mid, idx << 1);
    node B = range_query(mid + 1, R, mid + 1, r, idx << 1 | 1);
    return mergeNode(A, B);
}

// HLD：对路径 [x..y] 做“先查后更”（每段先查再加）
int path_add_and_query_maxdiff(int x, int y, int addv) {
    node leftPart, rightPart; // 默认空段（mx=INT_MIN, mn=INT_MAX, lmax/rmax=INT_MIN）

    while (top[x] != top[y]) {
        if (dep[top[x]] >= dep[top[y]]) {
            // 取到链顶 [top[x], x]，存储方向是 top->x，但路径方向是 x->...，要反转
            node cur = range_query(dfn[top[x]], dfn[x], 1, n, 1);
            range_add(dfn[top[x]], dfn[x], 1, n, 1, addv);
            cur = rev(cur); // ★ 方向修正
            leftPart = mergeNode(leftPart, cur);
            x = fa[top[x]];
        }
        else {
            // 右侧取 [top[y], y]，最终路径方向是 ...->y，与存储方向一致，不反转
            node cur = range_query(dfn[top[y]], dfn[y], 1, n, 1);
            range_add(dfn[top[y]], dfn[y], 1, n, 1, addv);
            rightPart = mergeNode(cur, rightPart); // ★ 当前块在右侧“更靠右”，应当前置
            y = fa[top[y]];
        }
    }
    // 同一条链
    if (dfn[x] <= dfn[y]) {
        node mid = range_query(dfn[x], dfn[y], 1, n, 1); // 方向一致
        range_add(dfn[x], dfn[y], 1, n, 1, addv);
        node all = mergeNode(leftPart, mergeNode(mid, rightPart));
        return all.lmax; // 整条路径的 A[j]-A[i] 最大值
    }
    else {
        node mid = range_query(dfn[y], dfn[x], 1, n, 1); // 存储方向 y->x，但路径要 x->y
        range_add(dfn[y], dfn[x], 1, n, 1, addv);
        mid = rev(mid); // ★ 方向修正
        node all = mergeNode(leftPart, mergeNode(mid, rightPart));
        return all.lmax;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    fa.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    top.assign(n + 1, 0);
    son.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    seg.assign(n + 1, 0);
    dep.assign(n + 1, 0);
    arr.assign(n + 1, 0);
    graph.assign(n + 1, {});
    sumv.assign(4 * n + 5, node());

    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    // 用 0 做虚父亲，深度干净
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);

    cin >> q;
    while (q--) {
        int x, y, v;
        cin >> x >> y >> v;
        int ans = path_add_and_query_maxdiff(x, y, v);
        cout << ans << '\n';
    }
    return 0;
}
