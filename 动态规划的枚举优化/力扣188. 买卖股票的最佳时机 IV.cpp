#include<iostream>
#include<vector>
using namespace std;
//无空间压缩版本
class Solution {
public:
    int f1(vector<int>& prices) {
        int ans = 0;
        int n = prices.size();
        for (int i = 1;i < n;i++) {
            ans += max(prices[i] - prices[i - 1], 0);
        }
        return ans;
    }
    int maxProfit(int k, vector<int>& prices) {
        return f2(k, prices);
        int n = prices.size();
        if (k >= n / 2)return f1(prices);
        vector<vector<int>>dp(n, vector<int>(k + 1, 0));
        for (int i = 1;i < n;i++) {
            for (int j = 1;j <= k;j++) {
                dp[i][j] = dp[i - 1][j];
                for (int z = 0;z < i;z++) {
                    dp[i][j] = max(dp[i][j], dp[z][j - 1] + prices[i] - prices[z]);
                }
            }
        }
        return dp[n - 1][k];
    }
    //空间压缩版本是两个数组滚动更新
    //这个版本是优化枚举版本
    int f2(int k, vector<int>& prices) {
        int n = prices.size();
        if (k >= n / 2)return f1(prices);
        vector<vector<int>>dp(k + 1, vector<int>(n, 0));
        for (int i = 1;i <= k;i++) {
            int best = dp[i - 1][0] - prices[0];
            for (int j = 1;j < n;j++) {
                dp[i][j] = max(dp[i][j - 1], best + prices[j]);
                best = max(best, dp[i - 1][j] - prices[j]);
            }
        }
        return dp[k][n - 1];
    }
};

