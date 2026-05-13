#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>dp(n,vector<int>(2,INT_MIN));
        dp[0][0] = nums[0];
        dp[0][1] = nums[0];
        int mn = dp[0][0];
        int sum = nums[0];
        int mx = dp[0][1];
        for (int i = 1; i < n; i++) {
            dp[i][0] = min(dp[i - 1][0] + nums[i], nums[i]);
            dp[i][1] = max(dp[i][1] + nums[i], nums[i]);
            mn = min(mn, dp[i][0]);
            mx = max(mx, dp[i][1]);
            sum += nums[i];
        }
        if (mn == sum)return mx;
        return max(sum - mn, mx);
    }
};