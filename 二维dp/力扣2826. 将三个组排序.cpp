#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int i,vector<vector<int>>&dp, int n, vector<int>& nums, int pre) {
        if (i == n)return 0;
        if (dp[i][pre] != -1)return dp[i][pre];
        int ans = dfs(i + 1, dp, n, nums, pre);
        if (nums[i] >= pre) {
            ans = min(ans, dfs(i + 1, dp, n, nums, nums[i]));
        }
        dp[i][pre] = ans;
        return ans;
    }
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>dp(n, vector<int>(4, -1));
        return  dfs(0,dp, n, nums, 0);
    }
};