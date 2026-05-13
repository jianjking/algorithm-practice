#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
//相当于爬楼梯
//dp[i]的含义是从i到n有多少种方法
class Solution {
public:
    int countTexts(string s) {
        int n = s.size();
        vector<long long>dp(n + 1, 1);
        for (int i = n - 2;i >= 0;i--) {
            dp[i] = dp[i + 1];
            if (s[i] == s[i + 1])dp[i] += dp[i + 2];
            if (i + 2 < n &&s[i]==s[i+1]&&s[i] == s[i + 2])dp[i] += dp[i + 3];
            if (i + 3 < n && s[i] == s[i + 3] && s[i] == s[i + 1] && s[i] == s[i + 2]&&(s[i]=='7'||s[i]=='9'))dp[i] += dp[i + 4];
            dp[i] = dp[i] % mod;
        }
        return dp[0];
    }
};