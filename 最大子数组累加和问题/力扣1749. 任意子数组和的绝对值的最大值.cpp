#include<iostream>
#include<vector>
using namespace std;
//ø’º‰—πÀı
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        int ans1 = nums[0];
        int ans2 = nums[0];
        int pre = nums[0];
        int cur = nums[0];
        for (int i = 1;i < n;i++) {
            pre = max(pre + nums[i], nums[i]);
            cur = min(nums[i], nums[i] + cur);
            ans1 = min(ans1, cur);
            ans2 = max(ans2, pre);
        }
        return max(abs(ans1), abs(ans2));
    }
};
class Solution {
public:
    //∑«ø’º‰—πÀı
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>dp(n, vector<int>(2, 0));
        dp[0][0] = dp[0][1] = nums[0];
        int ans1 = nums[0];
        int ans2 = nums[0];
        for (int i = 1;i < n;i++) {
            dp[i][0] = max(dp[i - 1][0] + nums[i], nums[i]);
            dp[i][1] = min(nums[i], nums[i] + dp[i - 1][1]);
            ans1 = min(ans1, dp[i][1]);
            ans2 = max(ans2, dp[i][0]);
        }
        return max(abs(ans1), abs(ans2));
    }
};