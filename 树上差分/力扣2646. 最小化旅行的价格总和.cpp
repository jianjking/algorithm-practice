#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void  dfs(int son, int father, int limit, vector<vector<int>>& st, vector<vector<int>>& graph, vector<int>& deep) {
        deep[son] = deep[father] + 1;
        st[son][0] = father;
        for (int i = 1;i <= limit;i++) {
            st[son][i] = st[st[son][i - 1]][i - 1];
        }
        for (auto& p : graph[son]) {
            if (p != father) {
                dfs(p, son, limit, st, graph, deep);
            }
        }
    }
    int power(int n) {
        int p = 0;
        while ((1 << p) <= (n >> 1))p++;
        return p;
    }
    void dfs1(int son, int father, vector<int>& cnt, vector<vector<int>>& graph) {
        for (auto& p : graph[son]) {
            if (p != father)dfs1(p, son, cnt, graph);
        }
        for (auto& p : graph[son]) {
            if (p != father)cnt[son] += cnt[p];
        }
    }
    pair<int, int> dp(int son, int father, vector<int>& price, vector<int>& cnt, vector<vector<int>>& graph) {
        pair<int, int>ret;
        ret.first = cnt[son] * price[son - 1];
        ret.second = ret.first / 2;
        for (auto& p : graph[son]) {
            if (p != father) {
                pair<int, int>tmp = dp(p, son, price, cnt, graph);
                ret.first += min(tmp.first, tmp.second);
                ret.second += tmp.first;
            }
        }
        return ret;
    }
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<vector<int>>graph(n + 1);
        for (auto& p : edges) {
            int a = p[0] + 1;
            int b = p[1] + 1;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vector<int>cnt(n + 1, 0);
        vector<int>deep(n + 1, 0);
        int limit = power(n);
        vector<vector<int>>st(n + 1, vector<int>(limit + 1, 0));
        dfs(1, 0, limit, st, graph, deep);

        for (auto& p : trips) {
            int a = p[0] + 1;
            int b = p[1] + 1;
            cnt[a]++;
            cnt[b]++;
            if (deep[a] < deep[b])swap(a, b);
            for (int i = limit;i >= 0;i--) {
                if (deep[st[a][i]] >= deep[b]) {
                    a = st[a][i];
                }
            }
            int c;
            if (a == b)c = a;
            else {
                for (int i = limit;i >= 0;i--) {
                    if (st[a][i] != st[b][i]) {
                        a = st[a][i];
                        b = st[b][i];
                    }
                }
                c = st[a][0];
            }
            cnt[c]--;
            cnt[st[c][0]]--;
        }
        dfs1(1, 0, cnt, graph);
        pair<int, int>ans = dp(1, 0, price, cnt, graph);
        return min(ans.first, ans.second);
    }
};