#include<iostream>
#include<vector>
#include<bit>
using namespace std;
class Solution {
public:
    // dfs 构建深度、距离数组 和 祖先表 p[son][0] = father
    void dfs(vector<int>& dis, vector<int>& depth, vector<vector<pair<int, int>>>& graph, vector<vector<int>>& p, int son, int father) {
        p[son][0] = father;
        for (auto& p1 : graph[son]) {
            if (p1.first == father) continue; // 避免走回头路
            depth[p1.first] = depth[son] + 1; // 更新深度
            dis[p1.first] = dis[son] + p1.second; // 累加距离
            dfs(dis, depth, graph, p, p1.first, son); // 递归子节点
        }
    }

    // 计算 a 和 b 之间的距离
    int get(int a, int b, vector<vector<int>>& p, vector<int>& depth, vector<int>& dis, int m) {
        int a1 = a;
        int b1 = b;
        if (depth[a] > depth[b]) swap(a, b); // 确保 a 比 b 深度小

        // 让 b 先跳到和 a 同样的深度
        int k = depth[b] - depth[a];
        for (; k; k &= (k - 1)) {
            b = p[b][__builtin_ctz(k)]; // __builtin_ctz(k) 是最低位的1在哪（用于快速跳跃）
        }

        // 向上跳直到找到 LCA（最近公共祖先）
        for (int i = m; i >= 0; i--) {
            if (p[a][i] != p[b][i]) {
                a = p[a][i];
                b = p[b][i];
            }
        }

        // 如果 a == b，说明它就是最近公共祖先；否则是它们的父节点
        int lca = (a == b ? a : p[a][0]);

        // 距离公式：dis[u] + dis[v] - 2 * dis[lca]
        return dis[a1] + dis[b1] - 2 * dis[lca];
    }

    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1; // 假设节点从 0 开始编号
        vector<vector<pair<int, int>>> graph(n); // 邻接表：每个节点 -> (邻居, 权重)

        // 构建图
        for (auto& p : edges) {
            int a = p[0], b = p[1], c = p[2];
            graph[a].push_back({ b, c });
            graph[b].push_back({ a, c });
        }

        // 计算跳表最大深度 m（log2(n) 向上取整）
        int m = 0, tmp = n;
        while (tmp) {
            tmp /= 2;
            m++;
        }

        // p[i][j] 表示节点 i 的第 2^j 个祖先
        vector<vector<int>> p(n, vector<int>(m + 1, -1));
        vector<int> dis(n, 0);     // 到根节点的距离
        vector<int> depth(n, 0);   // 深度

        // 从根节点 0 开始 DFS 建树
        dfs(dis, depth, graph, p, 0, -1);

        // 构建倍增表 p[i][j] = p[ p[i][j-1] ][j-1]
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int tmp = p[j][i];
                if (tmp != -1) {
                    p[j][i + 1] = p[tmp][i];
                }
            }
        }

        vector<int> ans(queries.size());

        // 每个查询有三个点 a, b, c，计算它们之间的路径长度之和除以2
        for (int i = 0; i < queries.size(); i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            int c = queries[i][2];

            // 利用 get 函数求出三对之间的路径和
            ans[i] = (get(a, b, p, depth, dis, m) + get(a, c, p, depth, dis, m) + get(b, c, p, depth, dis, m)) / 2;
        }

        return ans;
    }
};
