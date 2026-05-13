#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
class Solution {
public:
    void dfs(int i, vector<vector<int>>& graph, vector<bool>& vis) {
        vis[i] = true;
        for (int nxt : graph[i]) {
            if (!vis[nxt])           // ←—— 关键：不重复访问
                dfs(nxt, graph, vis);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>>graph(n);
        for (auto& p : invocations) {
            graph[p[0]].push_back(p[1]);
        }
        vector<bool>vis(n, false);
        vector<int>cnt(n, 0);
        dfs(k, graph, vis);
        for (auto& p : invocations) {
            if (!vis[p[0]])cnt[p[1]]++;
        }
        vector<int>ans1(n);
        for (int i = 0;i < n;i++) {
            ans1[i] = i;
        }
        vector<int>ans;
        for (int i = 0;i < n;i++) {
            if (vis[i] && cnt[i] != 0)return ans1;
            if (vis[i])continue;
            ans.push_back(i);

        }

        return ans;
    }
};