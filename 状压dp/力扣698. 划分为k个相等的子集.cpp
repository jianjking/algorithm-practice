#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int f(vector<int>& dp, int status, int limit, int a, int s, vector<int>& nums) {
        if (s == 0)return status == 0;
        if (dp[status] != -1)return dp[status];
        int n = nums.size();
        dp[status] = 0;
        for (int i = 0;i < n;i++) {
            if ((status & (1 << i)) != 0 && nums[i] + a <= limit) {
                if (nums[i] + a == limit) {
                    dp[status] = f(dp, status ^ (1 << i), limit, 0, s - 1, nums);
                    if (dp[status])break;
                }
                else {
                    dp[status] = f(dp, status ^ (1 << i), limit, a + nums[i], s, nums);
                    if (dp[status])break;
                }
            }
        }
        return dp[status];
    }
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        int n = nums.size();
        int sum = 0;
        for (int i = 0;i < n;i++) {
            sum += nums[i];
        }
        if (sum % k != 0)return false;
        int limit = sum / k;
        int status = (1 << (n)) - 1;
        vector<int>dp(1 << n, -1);
        return f(dp, status, limit, 0, k, nums);
    }
};