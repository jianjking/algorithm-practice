#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        // dp[i][j][k]:
        // i: 当前索引
        // j: 是否已经翻转过奇偶（0 表示未翻转，1 表示已翻转）
        // k: 当前数字的奇偶性（0 偶数，1 奇数）
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, 0)));

        dp[0][0][nums[0] % 2] = 1;
        dp[0][1][nums[0] % 2] = 1;

        for (int i = 1; i < n; ++i) {
            int parity = nums[i] % 2;
            if (parity == 0) {
                // 当前是偶数
                dp[i][0][0] = dp[i - 1][0][0] + 1;
                dp[i][0][1] = dp[i - 1][0][1];
                dp[i][1][0] = dp[i - 1][1][1] + 1;
                dp[i][1][1] = dp[i - 1][1][1];
            }
            else {
                // 当前是奇数
                dp[i][0][0] = dp[i - 1][0][0];
                dp[i][0][1] = dp[i - 1][0][1] + 1;
                dp[i][1][0] = dp[i - 1][1][0];
                dp[i][1][1] = dp[i - 1][1][0] + 1;
            }
        }

        return max({ dp[n - 1][0][0], dp[n - 1][0][1], dp[n - 1][1][0], dp[n - 1][1][1] });
    }
};
