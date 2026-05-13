#include<iostream>
#include<vector>
#include<deque>
using namespace std;
class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        // dp[i]: 划分前 i 个元素的方案数
        // pref[i]: dp[0] + dp[1] + ... + dp[i]
        vector<int> dp(n + 1), pref(n + 1);
        dp[0] = 1;
        pref[0] = 1;

        deque<int> maxd, mind;  // 存索引
        int left = 0;           // 滑动窗口左边界

        for (int i = 1; i <= n; ++i) {
            int x = nums[i - 1];

            // 维护最大值单调队列
            while (!maxd.empty() && nums[maxd.back()] <= x)
                maxd.pop_back();
            maxd.push_back(i - 1);

            // 维护最小值单调队列
            while (!mind.empty() && nums[mind.back()] >= x)
                mind.pop_back();
            mind.push_back(i - 1);

            // 如果窗口 [left, i-1] 不满足 max-min <= k，就移动 left
            while (!maxd.empty() && !mind.empty()
                && nums[maxd.front()] - nums[mind.front()] > k) {
                if (maxd.front() == left) maxd.pop_front();
                if (mind.front() == left) mind.pop_front();
                ++left;
            }

            // dp[i] = sum(dp[j]) for j in [left, i-1]
            int sum = pref[i - 1];
            if (left > 0) {
                sum = (sum - pref[left - 1] + MOD) % MOD;
            }
            dp[i] = sum;

            // 更新前缀和
            pref[i] = (pref[i - 1] + dp[i]) % MOD;
        }

        return dp[n];
    }
};
