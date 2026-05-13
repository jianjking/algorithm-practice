#include<iostream>
#include<vector>
#include<set>
using namespace std;

// 用 array<int,3> 表示状态 {u, lastColor, dist}
// 比较器按 dist -> u -> lastColor 排序，避免把不同颜色状态“当成一个”
struct Cmp {
    bool operator()(const array<int, 3>& a, const array<int, 3>& b) const {
        if (a[2] != b[2]) return a[2] < b[2]; // dist
        if (a[0] != b[0]) return a[0] < b[0]; // node
        return a[1] < b[1];                   // lastColor
    }
};

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n,
        vector<vector<int>>& redEdges,
        vector<vector<int>>& blueEdges) {

        // 颜色：0 = 红，1 = 蓝
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : redEdges)  g[e[0]].push_back({ e[1], 0 }); // 有向
        for (auto& e : blueEdges) g[e[0]].push_back({ e[1], 1 }); // 有向

        const int INF = 1e9;
        // dist[u][c] = 到达u且上一条边颜色为c的最短距离
        vector<vector<int>> dist(n, vector<int>(2, INF));

        set<array<int, 3>, Cmp> pq;
        // 起点：我们放入两种“上一条边颜色”的起始状态，距离都为0
        dist[0][0] = dist[0][1] = 0;
        pq.insert({ 0, 0, 0 }); // {u=0, lastColor=红, dist=0}
        pq.insert({ 0, 1, 0 }); // {u=0, lastColor=蓝, dist=0}

        while (!pq.empty()) {
            auto cur = *pq.begin(); pq.erase(pq.begin());
            int u = cur[0], last = cur[1], d = cur[2];

            // 过时状态
            if (d != dist[u][last]) continue;

            for (auto [v, col] : g[u]) {
                if (col == last) continue;        // 必须交替颜色
                int nd = d + 1;
                if (nd < dist[v][col]) {
                    dist[v][col] = nd;
                    pq.insert({ v, col, nd });
                }
            }
        }

        vector<int> ans(n, -1);
        for (int i = 0; i < n; ++i) {
            int d = min(dist[i][0], dist[i][1]);
            if (d < INF) ans[i] = d;
        }
        return ans;
    }
};
