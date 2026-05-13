#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int f(vector<vector<int>>& graph, vector<vector<int>>& dp, int status, int i) {
        if (status == 0)return 1;
        if (i == graph.size())return 0;
        if (dp[status][i] != -1)return dp[status][i];
        int ans = f(graph, dp, status, i + 1);
        for (auto& p : graph[i]) {
            if ((status & (1 << p)) != 0) {
                ans = (ans + f(graph, dp, status ^ (1 << p), i + 1)) % mod;
            }
        }
        dp[status][i] = ans;
        return ans;
    }
    int numberWays(vector<vector<int>>& hats) {
        int n = hats.size();
        int m = INT_MIN;
        for (int i = 0;i < n;i++) {
            for (auto& p : hats[i]) {
                m = max(m, p);
            }
        }
        vector<vector<int>>graph(m);
        for (int i = 0;i < n;i++) {
            for (auto& p : hats[i]) {
                graph[p - 1].push_back(i);
            }
        }
        int status = (1 << n) - 1;
        vector<vector<int>>dp(1 << n, vector<int>(m, -1));

        return f(graph, dp, status, 0);
    }
};