#include<iostream>
#include<vector>
using namespace std;

static const int MAXN = 300000 + 5;
static const int LOGN = 19; // 2^19 = 524288 > 300000

int n, m;

// ---- 邻接表存储树 ----
vector<pair<int, int>> adj[MAXN];

// ---- LCA 相关数组 ----
int depthArr[MAXN];
long long distArr[MAXN];
int parentArr[MAXN][LOGN + 1];

// 递归 DFS：计算 depthArr[u], distArr[u], parentArr[u][0]
void dfsBuild(int u, int p) {
    for (auto& e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == p) continue;
        parentArr[v][0] = u;
        depthArr[v] = depthArr[u] + 1;
        distArr[v] = distArr[u] + w;
        dfsBuild(v, u);
    }
}

// 计算 LCA(u, v)
int lca(int u, int v) {
    if (depthArr[u] < depthArr[v]) swap(u, v);
    int diff = depthArr[u] - depthArr[v];
    for (int k = 0; k <= LOGN; k++) {
        if (diff & (1 << k)) {
            u = parentArr[u][k];
        }
    }
    if (u == v) return u;
    for (int k = LOGN; k >= 0; k--) {
        if (parentArr[u][k] != parentArr[v][k]) {
            u = parentArr[u][k];
            v = parentArr[v][k];
        }
    }
    return parentArr[u][0];
}

// ---- 查询端点与代价 ----
int qusu[MAXN], qusv[MAXN];
int lcaArr[MAXN];
long long costArr[MAXN];
long long maxCost;

// 差分计数与 DFS 检查
int numCnt[MAXN];
int beyondCnt;    // 超过 limit 的查询数
int atLeastVal;   // = maxCost - limit

// 递归检查：看是否存在一条树边可以将其权重置为 0
bool dfsCheck(int u, int p, int w) {
    for (auto& e : adj[u]) {
        int v = e.first, wt = e.second;
        if (v == p) continue;
        if (dfsCheck(v, u, wt)) return true;
    }
    for (auto& e : adj[u]) {
        int v = e.first;
        if (v == p) continue;
        numCnt[u] += numCnt[v];
    }
    // 如果 u 不是根（1），且子树 u 中恰好聚集 beyondCnt 条超限查询，
    // 并且边 (u→p) 的权重 w >= atLeastVal，就可以把这条边置零
    if (u != 1 && numCnt[u] == beyondCnt && w >= atLeastVal) {
        return true;
    }
    return false;
}

// 检查给定 limit 是否可行
bool checkLimit(long long limit) {
    atLeastVal = int(maxCost - limit);
    memset(numCnt + 1, 0, sizeof(int) * n);
    beyondCnt = 0;
    for (int i = 1; i <= m; i++) {
        if (costArr[i] > limit) {
            int u = qusu[i], v = qusv[i], a = lcaArr[i];
            numCnt[u]++;
            numCnt[v]++;
            numCnt[a] -= 2;
            beyondCnt++;
        }
    }
    if (beyondCnt == 0) return true;
    return dfsCheck(1, 0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    // 读入树的 n-1 条边
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        depthArr[i] = 0;
        distArr[i] = 0;
        for (int k = 0; k <= LOGN; k++) {
            parentArr[i][k] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // 构建 LCA：先从根 1 递归计算 depthArr, distArr, parentArr[][0]
    depthArr[1] = 0;
    distArr[1] = 0;
    parentArr[1][0] = 0;
    dfsBuild(1, 0);

    // 二进制提升填 parentArr[u][k]
    for (int k = 1; k <= LOGN; k++) {
        for (int u = 1; u <= n; u++) {
            int mid = parentArr[u][k - 1];
            parentArr[u][k] = mid ? parentArr[mid][k - 1] : 0;
        }
    }

    // 读 m 条查询，直接计算 LCA 和路径代价
    maxCost = 0;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        qusu[i] = u;
        qusv[i] = v;
        int a = lca(u, v);
        lcaArr[i] = a;
        long long c = distArr[u] + distArr[v] - 2LL * distArr[a];
        costArr[i] = c;
        if (c > maxCost) maxCost = c;
    }

    // 在 [0, maxCost] 区间做二分
    long long lo = 0, hi = maxCost;
    while (lo < hi) {
        long long mid = (lo + hi) >> 1;
        if (checkLimit(mid)) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << lo << "\n";
    return 0;
}
