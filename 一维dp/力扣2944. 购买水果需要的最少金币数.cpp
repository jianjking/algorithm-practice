#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        // dp[i]: 从第 i 果子开始拿完要花的钱，i 从 1 到 n+1
        vector<int> dp(n + 2, INT_MAX);
        dp[n + 1] = 0;  // 边界：第 n+1 个虚拟位置不需花钱

        // 自底向上填表
        for (int i = n; i >= 1; --i) {
            if (2 * i >= n) {
                // 买第 i 果子就能拿完剩下所有
                dp[i] = prices[i - 1];
            }
            else {
                int limit = min(2 * i + 1, n + 1);
                int best = INT_MAX;
                // 在 i+1 到 limit 范围内选个最优
                for (int j = i + 1; j <= limit; ++j) {
                    best = min(best, dp[j]);
                }
                dp[i] = prices[i - 1] + best;
            }
        }
        return dp[1];
    }
};
