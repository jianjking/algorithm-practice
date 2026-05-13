#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int f(int a, int b, vector<vector<int>>& dp) {
        if (a == 0)return b == 0;
        if (a == 1)return 1;
        if (dp[a][b] != -1)return dp[a][b];
        if (b) {
            dp[a][b] = (f(a - 1, 1, dp) + f(a - 1, 0, dp)) % mod;
        }
        else {
            dp[a][b] = (f(a - 1, 0, dp) + f(a - 2, 0, dp) + (long long)2 * f(a - 2, 1, dp)) % mod;
        }
        return dp[a][b];
    }
    int numTilings(int n) {
        vector<vector<int>>dp(n + 1, vector<int>(2, -1));
        return f(n, 0, dp);
    }
};