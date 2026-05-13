#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& p : roads) {
            graph[p[0]].emplace_back(p[1], p[2]);
            graph[p[1]].emplace_back(p[0], p[2]);
        }

        vector<bool> visited(n + 1, false);
        queue<int> q;
        int ans = INT_MAX;

        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& p : graph[u]) {
                ans = min(ans, p.second); // 每条边都统计
                if (!visited[p.first]) {
                    visited[p.first] = true;
                    q.push(p.first);
                }
            }
        }

        return ans;
    }
};
