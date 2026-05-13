//http://poj.org/problem?id=3417
#include<iostream>
#include<vector>
using namespace std;

/*
  下面的实现沿用了你原来代码的整体框架，只作两处关键修改：

  1) dfs1 中不再把 cnt[v] 累加到 graph[u][idx].second 里，也不在邻接表里储存“权重”。
     只做 cnt[u] += cnt[v]，让 cnt[x] 最终表示“经过节点 x 的新边（做差分后）数量”。

  2) 最后统计时，针对每个 2 ≤ u ≤ n，令 parent = st[u][0]，新边/环路“经过老边 (parent–u)” 的次数
     就等于 cnt[u]。一条老边如果被经过 0 次，答案加 m；被经过 1 次，答案加 1；≥2 次则加 0。
     这样就只计算每条树边一次，不需要再“沿邻接表双向累加再除 2”来去重。

  其它（LCA 预处理、差分、第二次累加）都与之前思路相同。
*/

void dfs(int son, int father, int limit, vector<int>& deep, vector<vector<int>>& st, vector<vector<int>>& graph) {
    deep[son] = 1 + deep[father];
    st[son][0] = father;
    for (int i = 1; i <= limit; i++) {
        st[son][i] = st[st[son][i - 1]][i - 1];
    }
    // 原来是： for (auto& p : graph[son]) ...
    // 改成索引循环，graph[son][idx] 只存邻居编号
    for (size_t idx = 0; idx < graph[son].size(); idx++) {
        int v = graph[son][idx];
        if (v != father) {
            dfs(v, son, limit, deep, st, graph);
        }
    }
}

int power(int n) {
    int p = 0;
    while ((1 << p) <= (n >> 1)) p++;
    return p;
}

void dfs1(int son, int father, vector<int>& cnt, vector<vector<int>>& graph) {
    // 先遍历孩子，把 cnt[child] 都算出来
    for (size_t idx = 0; idx < graph[son].size(); idx++) {
        int v = graph[son][idx];
        if (v != father) {
            dfs1(v, son, cnt, graph);
        }
    }
    // 再把每个孩子 v 的 cnt[v] 累加到 cnt[son]
    for (size_t idx = 0; idx < graph[son].size(); idx++) {
        int v = graph[son][idx];
        if (v != father) {
            cnt[son] += cnt[v];
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 这里把图简化为：graph[u] 存储所有与 u 相邻的点编号，
    // 不再用 pair<int,int>，因为我们不在邻接表里储“权重”了。
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 计算跳表层数 limit = floor(log2(n))
    int limit = power(n);

    // st[u][k] 表示：u 向上跳 2^k 层的祖先
    vector<vector<int>> st(n + 1, vector<int>(limit + 1, 0));
    // 深度数组
    vector<int> deep(n + 1, 0);

    // 1) 先从根 1 做一次 dfs，把 deep[] 和 st[][0] … st[][limit] 都算好
    dfs(1, 0, limit, deep, st, graph);

    // cnt[x] 用来做节点差分
    vector<int> cnt(n + 1, 0);

    // 2) 读入 m 条“新边”，做差分：cnt[u]++，cnt[v]++，cnt[lca] -= 2
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        cnt[a]++;
        cnt[b]++;
        // 先把 a,b 拉到同一深度
        if (deep[a] < deep[b]) swap(a, b);
        for (int j = limit; j >= 0; j--) {
            if (deep[st[a][j]] >= deep[b]) {
                a = st[a][j];
            }
        }
        int c;
        if (a == b) {
            c = a;
        }
        else {
            for (int j = limit; j >= 0; j--) {
                if (st[a][j] != st[b][j]) {
                    a = st[a][j];
                    b = st[b][j];
                }
            }
            c = st[a][0];
        }
        cnt[c] -= 2;
    }

    // 3) 第二次 DFS，把每个子节点的 cnt[v] 累加到 cnt[u]
    dfs1(1, 0, cnt, graph);

    // 4) 统计答案：对于 tree 中的每条无向边 (parent,u)，经过次数就是 cnt[u]
    //    如果 cnt[u] == 0，则这条老边可以和任意一条 m 条新边配对 → 加 m
    //    如果 cnt[u] == 1，则加 1； >=2 则加 0。
    long long ans = 0;
    for (int u = 2; u <= n; u++) {
        int w = cnt[u];
        if (w == 0)       ans += m;
        else if (w == 1)  ans += 1;
        // w >= 2 时加 0，不写也行
    }

    printf("%lld\n", ans);
    return 0;
}
