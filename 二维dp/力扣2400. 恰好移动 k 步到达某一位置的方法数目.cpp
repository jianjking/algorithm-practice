#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
int dfs(int i, int remain, int end, vector<vector<int>>&dp) {
    if (remain == 0) {
        return i == end ? 1 : 0;
    }
    if (dp[i][remain] != -1)return dp[i][remain];
    int& res = dp[i][remain];
    res = 0;
    res = (res + dfs(i + 1, remain - 1, end, dp) + dfs(i - 1, remain - 1, end, dp)) % mod;
    return res;
}
class Solution {
public:
    int numberOfWays(int startPos, int endPos, int k) {
        vector<vector<int>>dp(3000, vector<int>(k+1, -1));
        return dfs(startPos + 1000, k, endPos + 1000, dp);
    }
};