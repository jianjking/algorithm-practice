#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

class Solution {
public:
    int numWays(int steps, int len) {
        // 实际上只会走到下标 <= steps 的位置，超过也到不了
        int maxPos = min(len - 1, steps);

        // dp[i] 表示当前步数下，在位置 i 的方案数
        vector<long long> dp(maxPos + 1, 0), ndp(maxPos + 1, 0);
        dp[0] = 1; // 0 步在 0 位置只有 1 种方案

        for (int s = 1; s <= steps; ++s) {
            // 每一轮都重新算 ndp
            for (int i = 0; i <= maxPos; ++i) {
                long long ways = dp[i]; // 原地不动
                if (i - 1 >= 0)        ways += dp[i - 1]; // 从左边走过来
                if (i + 1 <= maxPos)   ways += dp[i + 1]; // 从右边走过来
                ndp[i] = ways % mod;
            }
            // 滚动：当前 dp 变成上一层
            dp.swap(ndp);
            // 清空 ndp 也可以不清，下一轮会被完全覆盖
        }

        // 走完 steps 步，在位置 0 的方案数
        return (int)dp[0];
    }
};
