#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    // 按照题目键盘布局，预先写好每个键可以跳到的目标键集合
    const vector<vector<int>> moves = {
        {4,6},    // 0
        {6,8},    // 1
        {7,9},    // 2
        {4,8},    // 3
        {3,9,0},  // 4
        {},       // 5 (中间点，马步到不了)
        {1,7,0},  // 6
        {2,6},    // 7
        {1,3},    // 8
        {2,4}     // 9
    };

    int knightDialer(int n) {
        // dp[d] = 当目前长度为 k 时，以键 d 结尾的方案数
        vector<int> dp(10, 1), next_dp(10);
        // 长度为 1 的时候，每个键都算 1 种
        for (int len = 2; len <= n; ++len) {
            fill(next_dp.begin(), next_dp.end(), 0);
            // 从上一轮「以 d 结尾」的所有方案，跳到它能到的每个 targ
            for (int d = 0; d < 10; ++d) {
                if (dp[d] == 0) continue;
                for (int targ : moves[d]) {
                    next_dp[targ] = (next_dp[targ] + dp[d]) % MOD;
                }
            }
            dp.swap(next_dp);
        }
        // 最终答案 = 所有键结尾的方案数之和
        int ans = 0;
        for (int x : dp) ans = (ans + x) % MOD;
        return ans;
    }
};
