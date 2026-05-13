#include<iostream>
#include<vector>
using namespace std;
void dfs(int u, const vector<vector<int>>& g, vector<int>& ans, const vector<int>& quiet) {
    if (ans[u] != -1) return;           // 记忆化
    int best = u;                        // 先选自己
    for (int v : g[u]) {                 // v 是更富的人
        dfs(v, g, ans, quiet);
        int cand = ans[v];
        if (quiet[cand] < quiet[best] ||
            (quiet[cand] == quiet[best] && cand < best)) { // 可选：相同安静度取更小下标
            best = cand;
        }
    }
    ans[u] = best;
}

class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> g(n);
        for (auto& e : richer) {
            // e[0] 更富于 e[1]，从“穷 -> 富”建反图，方便往上追
            g[e[1]].push_back(e[0]);
        }
        vector<int> ans(n, -1);
        for (int i = 0; i < n; ++i) dfs(i, g, ans, quiet);
        return ans;
    }
};
