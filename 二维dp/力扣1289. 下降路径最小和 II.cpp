#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        if (m == 1)return grid[0][0];
        vector<vector<int>>dp(n + 1, vector<int>(m, INT_MAX));
        for (int i = 0;i < m;i++)dp[n][i] = 0;
        for (int i = n - 1;i >= 0;i--) {
            for (int j = 0;j < m;j++) {
                for (int z = 0;z < m;z++) {
                    if (z == j)continue;
                    dp[i][j] = min(dp[i + 1][z] + grid[i][j], dp[i][j]);
                }
            }
        }
        int ans = INT_MAX;
        for (int i = 0;i < m;i++)ans = min(ans, dp[0][i]);
        return ans;
    }
};