#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        vector<vector<int>>dp(n, vector<int>(n, INT_MAX));
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                if (i > 0)dp[i][i - 1] = 1;
                if (i + 1 < n)dp[i][i + 1] = 1;
            }
        }
        dp[x][y] = 1;
        dp[y][x] = 1;
        for (int i = 0;i, n;i++) {
            for (int j = 0;j < n;j++) {
                for (int z = 0;z < n;z++) {
                    if (dp[j][i] != INT_MAX && dp[i][z] != INT_MAX && dp[i][z] + dp[j][i] < dp[j][z])dp[j][z] = dp[i][z] + dp[j][i];
                }
            }
        }
        vector<int>ans(n, 0);
        for (int i = 0;i < n;i++) {
            for (int j = 1;j < n;j++) {
                ans[dp[i][j]]++;
            }
        }
        return ans;
    }
};