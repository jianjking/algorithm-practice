#include<iostream>
#include<vector>
#include<set>

using namespace std;
class Graph {
public:
    vector<vector<pair<int, int>>> graph;
    int num;
    Graph(int n, vector<vector<int>>& edges) {
        graph.resize(n);
        for (auto& p : edges) {
            graph[p[0]].push_back({ p[1], p[2] });
        }
        num = n;
    }

    void addEdge(vector<int> edge) {
        graph[edge[0]].push_back({ edge[1], edge[2] });
    }

    int shortestPath(int node1, int node2) {
        vector<int> dist(num, INT_MAX);
        dist[node1] = 0;
        set<pair<int, int>> p; // {dist, node}
        p.insert({ 0, node1 });

        while (!p.empty()) {
            auto tmp = *p.begin();
            p.erase(p.begin());
            int b = tmp.first;
            int a = tmp.second;

            if (b > dist[a]) continue;
            if (a == node2) return b;

            for (auto& [c, w] : graph[a]) {
                if (dist[c] > b + w) {
                    dist[c] = b + w;
                    p.insert({ dist[c], c });
                }
            }
        }
        return -1;
    }
};

