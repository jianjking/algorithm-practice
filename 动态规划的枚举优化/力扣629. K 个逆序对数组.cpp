#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>>dp(n + 1, vector<int>(k + 1, 0));
        dp[1][0] = 1;
        for (int i = 2;i <= n;i++) {
            dp[i][0] = 1;
            int sum = 1;
            for (int j = 1;j <= k;j++) {
                if (i > j) {
                    sum = (sum + dp[i - 1][j]) % mod;
                }
                else {
                    sum = ((sum + dp[i - 1][j]) % mod - dp[i - 1][j - i] + mod) % mod;
                }
                dp[i][j] = sum;
            }
        }
        return dp[n][k];
    }
};

