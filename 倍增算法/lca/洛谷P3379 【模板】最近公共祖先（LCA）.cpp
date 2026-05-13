#include <iostream>
#include <vector>
using namespace std;

int power(int n) {
    int p = 0;
    while ((1 << p) <= n) p++;
    return p;
}

void dfs(int son, int father, vector<int>& deep,
    vector<vector<int>>& st, vector<vector<int>>& graph, int limit) {
    if (father == 0) {
        deep[son] = 1;
    }
    else {
        deep[son] = deep[father] + 1;
    }

    st[son][0] = father;
    for (int i = 1; i <= limit; i++) {
        if (st[son][i - 1] != 0)
            st[son][i] = st[st[son][i - 1]][i - 1];
        else
            st[son][i] = 0;
    }

    for (auto& p : graph[son]) {
        if (p != father)
            dfs(p, son, deep, st, graph, limit);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> deep(n + 1);
    int limit = power(n);
    vector<vector<int>> st(n + 1, vector<int>(limit + 1, 0));
    dfs(s, 0, deep, st, graph, limit);

    while (m--) {
        int a, b;
        cin >> a >> b;

        if (deep[a] < deep[b]) swap(a, b);

        // Step 1: a 跳到与 b 同层
        for (int i = limit; i >= 0; i--) {
            if (st[a][i] != 0 && deep[st[a][i]] >= deep[b]) {
                a = st[a][i];
            }
        }

        if (a == b) {
            cout << a << '\n';
            continue;
        }

        // Step 2: 同时往上跳，直到跳到同一个父亲
        for (int i = limit; i >= 0; i--) {
            if (st[a][i] != 0 && st[a][i] != st[b][i]) {
                a = st[a][i];
                b = st[b][i];
            }
        }

        cout << st[a][0] << '\n';  // LCA 是 a 和 b 的共同父亲
    }

    return 0;
}
