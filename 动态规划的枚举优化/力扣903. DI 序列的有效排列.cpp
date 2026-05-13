#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int f(string& s, int i, int size, int n) {
        if (i == n)return 1;
        int ans = 0;
        if (i == 0 || s[i - 1] == 'D') {
            for (int j = 0;j < size;j++) {
                ans = (ans + f(s, i + 1, j, n)) % mod;
            }
        }
        else {
            for (int j = 0;j < n - i - size;j++) {
                ans = (ans + f(s, i + 1, j + size, n)) % mod;
            }
        }
        return ans;
    }
    int numPermsDISequence(string s) {
        int n = s.size() + 1;
        vector<vector<int>>dp(n + 1, vector<int>(n + 1,0));
        for (int i = 0;i <= n;i++) {
            dp[n][i] = 1;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == 0 || s[i - 1] == 'D') {
                dp[i][1] = dp[i + 1][0];
                for (int less = 2; less <= n; less++) {
                    dp[i][less] = (dp[i][less - 1] + dp[i + 1][less - 1]) % mod;
                }
            }
            else {
                dp[i][n - i - 1] = dp[i + 1][n - i - 1];
                for (int less = n - i - 2; less >= 0; less--) {
                    dp[i][less] = (dp[i][less + 1] + dp[i + 1][less]) % mod;
                }
            }
        }
        //枚举优化后的结果
        return dp[0][n];
        //无枚举优化也没有空间压缩
        return f(s, 0, s.size() + 1, s.size() + 1);
    }
};