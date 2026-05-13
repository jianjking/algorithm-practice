#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(const vector<vector<int>>& g, int u, int p, int t, int target, double prob, double& out) {
        int child = 0;
        for (int v : g[u]) if (v != p) child++;
        if (t == 0 || child == 0) {
            if (u == target) out = prob;
            return;
        }
        for (int v : g[u]) if (v != p) {
            dfs(g, v, u, t - 1, target, prob / child, out);
        }
    }

    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<vector<int>> g(n + 1);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        double ans = 0.0;
        dfs(g, 1, 0, t, target, 1.0, ans);
        return ans;
    }
};
