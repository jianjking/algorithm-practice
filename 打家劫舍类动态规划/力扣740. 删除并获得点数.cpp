#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//空间压缩版本懒得写了
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int n = nums.size();
        int m = 0;
        for (int i = 0;i < n;i++) {
            m = max(m, nums[i]);
        }
        sort(nums.begin(), nums.end());
        int cnt = nums[0];
        vector<int>sum(m + 1, 0);
        for (int i = 1;i < n;i++) {
            while (i < n && nums[i] == nums[i - 1]) {
                cnt += nums[i];
                i++;
            }
            sum[nums[i - 1]] = cnt;
            if (i < n)
                cnt = nums[i];

        }
        sum[nums[n - 1]] = cnt;
        int ans = 0;
        vector<int>dp(m + 1, 0);
        dp[0] = sum[0];
        dp[1] = max(sum[0], sum[1]);
        for (int i = 2;i <= m;i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + sum[i]);
        }
        return dp[m];

    }
};
