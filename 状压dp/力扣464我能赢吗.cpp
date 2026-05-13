#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int f(vector<int>& dp, int n, int total, int rest) {
        if (rest <= 0)return 0;
        if (dp[total] != -1)return dp[total];
        dp[total] = 0;
        for (int i = 1;i <= n;i++) {
            if ((total & (1 << i)) != 0 && !f(dp, n, total ^ (1 << i), rest - i)) {
                dp[total] = 1;
                break;
            }
        }
        return dp[total];
    }
    bool canIWin(int n, int sum) {
        vector<int>dp(1 << (n + 1), -1);
        int total;
        total = (1 << (n + 1)) - 1;
        if (n * (n + 1) / 2 < sum)return false;
        if (sum == 0)return true;
        return f(dp, n, total, sum);
    }
};