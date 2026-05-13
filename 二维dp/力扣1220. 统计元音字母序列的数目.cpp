#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int countVowelPermutation(int n) {
        vector<int>dp(5, 1);
        for (int i = 1;i < n;i++) {
            vector<int>tmp = dp;
            dp[0] = ((long long)tmp[1] + tmp[2] + tmp[4]) % mod;
            dp[1] = (tmp[0] + tmp[2]) % mod;
            dp[2] = (tmp[1] + tmp[3]) % mod;
            dp[3] = tmp[2] % mod;
            dp[4] = (tmp[2] + tmp[3]) % mod;
        }
        int ans = 0;
        for (auto& p : dp)ans = (ans + p) % mod;
        return ans;
    }

};