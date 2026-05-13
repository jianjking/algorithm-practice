#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void dfs(int son, int father, int v, int limit, vector<int>& deep, vector<vector<int>>& st, vector<vector<int>>& cnt, vector<vector<pair<int, int>>>& graph) {
        if (son == 0) {
            cnt[son].assign(27, 0);
        }
        else {
            cnt[son] = cnt[father];
            cnt[son][v]++;
        }
        if (son == 0) {
            deep[son] = 1;
        }
        else {
            deep[son] = deep[father] + 1;
        }
        st[son][0] = father;
        for (int i = 1;i <= limit;i++) {
            if (st[son][i - 1] != -1) {
                st[son][i] = st[st[son][i - 1]][i - 1];
            }
        }
        for (auto& p : graph[son]) {
            if (p.first != father) {
                dfs(p.first, son, p.second, limit, deep, st, cnt, graph);
            }
        }

    }
    int power(int n) {
        int p = 0;
        while ((1 << p) <= (n >> 1))p++;
        return p;
    }
    int lca(int a, int b, int limit, vector<int>& deep, vector<vector<int>>& st) {
        if (deep[a] < deep[b])swap(a, b);
        for (int i = limit;i >= 0;i--) {
            if (st[a][i] != -1 && deep[st[a][i]] >= deep[b]) {
                a = st[a][i];
            }
        }
        if (a == b)return b;
        for (int i = limit;i >= 0;i--) {
            if (st[a][i] != st[b][i]) {
                a = st[a][i];
                b = st[b][i];
            }
        }
        return st[a][0];

    }

    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, int>>>graph(n);
        for (int i = 0;i < edges.size();i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            graph[u].push_back({ v,w });
            graph[v].push_back({ u,w });
        }
        int limit = power(n);
        vector<int>deep(n);
        vector<vector<int>>st(n, vector<int>(limit + 1, -1));
        vector<vector<int>>cnt(n, vector<int>(27, 0));
        dfs(0, 0, 1, limit, deep, st, cnt, graph);
        int m = queries.size();
        vector<int>ans(m);
        for (int i = 0;i < m;i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            int c = lca(a, b, limit, deep, st);
            int all = 0;
            int mx = INT_MIN;
            for (int j = 1;j <= 26;j++) {
                int tmp = cnt[a][j] + cnt[b][j] - 2 * cnt[c][j];
                all += tmp;
                mx = max(mx, tmp);
            }
            ans[i] = all - mx;
        }
        return ans;

    }
};