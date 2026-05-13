#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int son, int father, vector<vector<int>>& graph, vector<bool>& hasApple) {
        int cnt = 0;
        for (auto& p : graph[son]) {
            if (p != father)cnt += dfs(p, son, graph, hasApple);
        }
        if (!hasApple[son] && !cnt)return 0;
        return cnt + (son == 0 ? 0 : 2);
    }
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>>graph(n);
        for (auto& p : edges) {
            graph[p[1]].push_back(p[0]);
            graph[p[0]].push_back(p[1]);
        }
        return dfs(0, 0, graph, hasApple);
    }
};