#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    void bfs(int start, vector<int>& dist, const vector<vector<int>>& graph) {
        deque<int> q;
        dist[start] = 0;
        q.push_back(start);
        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            for (int v : graph[u]) {
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.push_back(v);
                }
            }
        }
    }

    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            if (edges[i] != -1)
                graph[i].push_back(edges[i]);
        }

        vector<int> dist1(n, INT_MAX), dist2(n, INT_MAX);
        bfs(node1, dist1, graph);
        bfs(node2, dist2, graph);

        int ans = INT_MAX, num = -1;
        for (int i = 0; i < n; i++) {
            int cur = max(dist1[i], dist2[i]);
            if (cur < ans || (cur == ans && (num == -1 || i < num))) {
                ans = cur;
                num = i;
            }
        }
        return ans == INT_MAX ? -1 : num;
    }
};
