#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
//dp[i]是指第几位有多少种方法
class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int>dp(high + 1, 0);
        int m = zero > one ? one : zero;
        int a = max(zero, one);
        dp[m] = 1;
        if (!(a % m))dp[a] = 2;
        else dp[a] = 1;
        for (int i = m + 1;i <= high;i++) {
            if (i != a) {
                if (i - zero >= 0)dp[i] = (dp[i] + dp[i - zero]) % mod;
                if (i - one >= 0)dp[i] = (dp[i] + dp[i - one]) % mod;
            }

        }

        int ans = 0;
        for (int i = low;i <= high;i++) {
            ans = (ans + dp[i]) % mod;
        }
        return ans;
    }
};