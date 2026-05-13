#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int dfs(int n, int k, int target, int cur, int sum, vector<vector<int>>& dp) {
        if (sum == target)return cur == n ? 1 : 0;
        if (sum > target)return 0;
        if (cur >= n)return 0;
        if (dp[cur][sum] != -1)return dp[cur][sum];
        int ans = 0;
        for (int i = 1;i <= k;i++) {
            ans = (ans + dfs(n, k, target, cur + 1, sum + i, dp)) % mod;
        }
        dp[cur][sum] = ans;
        return ans;
    }
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>>dp(n, vector<int>(target + 1, -1));
        return dfs(n, k, target, 0, 0, dp);
    }
};