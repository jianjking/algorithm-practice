#include<iostream>
#include<vector>
using namespace std;
class TreeAncestor {
public:
    vector<vector<int>>graph;
    vector<int>deep;
    vector<vector<int>>st;
    int power(int n) {
        int p = 0;
        while ((1 << p) <= n) p++;
        return p;
    }

    void dfs(int son, int father) {
        if (father == -1) {
            deep[son] = 1;
        }
        else {
            deep[son] = deep[father] + 1;
        }
        if (son == 0)st[son][0] = 0;
        else st[son][0] = father;
        for (int i = 1; (1 << i) <= deep[son]; i++) {
            if (st[son][i - 1] != -1)
                st[son][i] = st[st[son][i - 1]][i - 1];
            else
                st[son][i] = -1;
        }

        for (auto p : graph[son]) {
            dfs(p, son);
        }
    }
    TreeAncestor(int n, vector<int>& parent) {
        graph.resize(n);
        for (int i = 0;i < parent.size();i++) {
            if (parent[i] != -1) {
                graph[parent[i]].push_back(i);
            }
        }
        deep.assign(n, 0);
        int limit = power(n);
        st.assign(n, vector<int>(limit + 1, -1));
        dfs(0, -1);
    }

    int getKthAncestor(int node, int k) {
        if (deep[node] <= k)return -1;
        if (k == 0)return  node;
        int limit = power(deep[node]);
        k = deep[node] - k;
        for (int i = limit;i >= 0;i--) {
            if (st[node][i] != -1 && deep[st[node][i]] >= k) {
                node = st[node][i];
            }

        }
        return node;
    }
};
