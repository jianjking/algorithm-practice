#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long numberOfWays(string s) {
        int n = s.size();
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(3, vector<long long>(4, 0)));

        dp[0][2][0] = 1; // 初始状态：还没选任何字符

        for (int i = 1; i <= n; ++i) {
            int curr = s[i - 1] - '0'; // 当前字符
            for (int last = 0; last <= 2; ++last) {
                for (int cnt = 0; cnt <= 3; ++cnt) {
                    // 不选当前字符
                    dp[i][last][cnt] += dp[i - 1][last][cnt];

                    // 选当前字符（若合法）
                    if (cnt < 3 && (last == 2 || curr != last)) {
                        dp[i][curr][cnt + 1] += dp[i - 1][last][cnt];
                    }
                }
            }
        }

        // 答案是：任意 last 值下，长度为 3 的合法序列个数
        return dp[n][0][3] + dp[n][1][3];
    }
};


class Solution {
public:
    long long numberOfWays(string s) {
        int tot0 = count(s.begin(), s.end(), '0'); // 总共多少个0
        long long ans = 0;
        int c0 = 0; // 当前遍历中遇到的0的数量

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '1') {
                // 当前字符是 '1'，统计前面有多少 0，后面有多少 0
                ans += 1LL * c0 * (tot0 - c0);
            }
            else {
                // 当前字符是 '0'
                int c1 = i - c0; // 前面出现过的 '1' 数量 = 总共的字符数 - 已出现的0
                ans += 1LL * c1 * (s.size() - tot0 - c1); // 后面的 '1' 数量 = 总共的 '1' - 已出现的
                c0++; // 当前这个 '0' 也加入
            }
        }

        return ans;
    }
};
