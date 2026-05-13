#include<iostream>
#include<vector>
const int mod = 1e9 + 7;
using namespace std;
//就是斐波那契数列可以用两个变量滚动更新
class Solution {
public:
    int countHousePlacements(int n) {
        if (n == 1)return 4;
        if (n == 2)return  9;
        vector<int>dp(n);
        dp[0] = 2;
        dp[1] = 3;
        for (int i = 2;i < n;i++) {
            dp[i] = ((long long)dp[i - 1] + dp[i - 2]) % mod;
        }
        return (int)(((long long)dp[n - 1] * dp[n - 1]) % mod);
    }
};