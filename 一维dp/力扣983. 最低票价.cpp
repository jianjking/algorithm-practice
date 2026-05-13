#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int i, int n, std::vector<int>& days, std::vector<int>& cost, std::vector<int>& dp) {
        if (i == n) return 0;
        int& res = dp[i];
        if (res != -1) return res;
        int p1 = lower_bound(days.begin(), days.end(), days[i] + 1) - days.begin();
        int p2 = lower_bound(days.begin(), days.end(), days[i] + 7) - days.begin();
        int p3 = lower_bound(days.begin(), days.end(), days[i] + 30) - days.begin();
        res = std::min({
            cost[0] + dfs(p1, n, days, cost, dp),
            cost[1] + dfs(p2, n, days, cost, dp),
            cost[2] + dfs(p3, n, days, cost, dp)
            });
        return res;
    }

    int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
        int n = days.size();
        std::vector<int> dp(n, -1);
        return dfs(0, n, days, costs, dp);
    }
};
