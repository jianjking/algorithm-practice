#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int checkRecord(int n) {
        vector<vector<int>>dp = { {1,1,0},{1,0,0} };
        for (int i = 1;i < n;i++) {
            vector<vector<int>>tmp = dp;
            dp[0][0] = (tmp[0][0] + tmp[0][1] + (long long)tmp[0][2]) % mod;
            dp[0][1] = tmp[0][0];
            dp[0][2] = tmp[0][1];
            dp[1][0] = ((long long)tmp[0][0] + tmp[0][1] + tmp[0][2] + tmp[1][0] + tmp[1][1] + tmp[1][2]) % mod;
            dp[1][1] = tmp[1][0];
            dp[1][2] = tmp[1][1];
        }
        int ans = 0;
        for (int i = 0;i < 2;i++) {
            for (int j = 0;j < 3;j++)ans = (ans + dp[i][j]) % mod;
        }
        return ans;
    }
};