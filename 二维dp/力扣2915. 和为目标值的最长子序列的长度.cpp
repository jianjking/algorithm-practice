#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(vector<int>& nums, int i, int sum, int n, int target, vector<vector<int>>& dp) {
        if (sum == target)return 0;
        if (sum > target)return INT_MIN;
        if (i == n)return INT_MIN;
        if (dp[i][sum] != -1)return dp[i][sum];
        int ans = 0;
        ans = max(dfs(nums, i + 1, sum, n, target, dp), 1 + dfs(nums, i + 1, sum + nums[i], n, target, dp));
        dp[i][sum] = ans;
        return ans;
    }
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>>dp(n, vector<int>(target + 1, -1));
        return max(dfs(nums, 0, 0, n,target,dp),-1);
    }
};