#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    static const int MAXV = 30;
    static const int MOD = 1000000007;
    static const int PRIME_CNT = 10;
    static const int LIMIT = 1 << PRIME_CNT;
    
    // 状态位掩码：own[i] 表示数字 i 分解后若合法所包含的质因子对应的位
    int own[MAXV + 1] = {
        0b0000000000, // 0 (unused)
        0b0000000000, // 1
        0b0000000001, // 2
        0b0000000010, // 3
        0b0000000000, // 4
        0b0000000100, // 5
        0b0000000011, // 6
        0b0000001000, // 7
        0b0000000000, // 8
        0b0000000000, // 9
        0b0000000101, // 10
        0b0000010000, // 11
        0b0000000000, // 12
        0b0000100000, // 13
        0b0000001001, // 14
        0b0000000110, // 15
        0b0000000000, // 16
        0b0001000000, // 17
        0b0000000000, // 18
        0b0010000000, // 19
        0b0000000000, // 20
        0b0000001010, // 21
        0b0000010001, // 22
        0b0100000000, // 23
        0b0000000000, // 24
        0b0000000000, // 25
        0b0000100001, // 26
        0b0000000000, // 27
        0b0000000000, // 28
        0b1000000000, // 29
        0b0000000111  // 30
    };

    int numberOfGoodSubsets(vector<int>& nums) {
        // 计数 1~30 出现次数
        vector<int> cnt(MAXV + 1, 0);
        for (int x : nums) {
            if (x >= 1 && x <= MAXV) cnt[x]++;
        }
        
        // dp[mask] 表示状态 mask 的方案数
        vector<int> dp(LIMIT, 0);
        // 子集为空时只有1种
        dp[0] = 1;
        // 处理所有1，1不改变质因子状态，只影响倍数
        for (int i = 0; i < cnt[1]; ++i) {
            dp[0] = (int)((2LL * dp[0]) % MOD);
        }
        
        // 遍历 2~30
        for (int i = 2; i <= MAXV; ++i) {
            int mask = own[i];
            int times = cnt[i];
            if (mask == 0 || times == 0) continue;
            // 倒序更新，避免重复使用同一数字
            for (int state = LIMIT - 1; state >= 0; --state) {
                if ((state & mask) == mask) {
                    long long add = (1LL * dp[state ^ mask] * times) % MOD;
                    dp[state] = (dp[state] + (int)add) % MOD;
                }
            }
        }
        // 统计所有非空子集
        int ans = 0;
        for (int s = 1; s < LIMIT; ++s) {
            ans = (ans + dp[s]) % MOD;
        }
        return ans;
    }
};
