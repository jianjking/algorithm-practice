#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>
#include<queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        vector<int> indeg(n, 0);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            indeg[v]++;
        }

        // 祖先集合：anc[i][j] == 1 表示 j 是 i 的祖先
        const int MAXN = 1005; // n <= 1000
        vector<bitset<MAXN>> anc(n);

        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                // v 继承 u 的所有祖先，并把 u 自己也记成 v 的祖先
                anc[v] |= anc[u];
                anc[v].set(u);
                if (--indeg[v] == 0) q.push(v);
            }
        }

        vector<vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            for (int a = 0; a < n; a++) if (anc[i].test(a)) ans[i].push_back(a);
            // 已经天然有序（按编号从小到大扫描）
        }
        return ans;
    }
};
