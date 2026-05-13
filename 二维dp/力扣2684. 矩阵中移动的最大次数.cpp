#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int i, int j, int n, int m, vector<vector<int>>& dp, vector<vector<int>>& grid) {
        if (j == m - 1)return 0;
        if (dp[i][j] != -1)return dp[i][j];
        dp[i][j] = 0;
        if (i - 1 >= 0 && grid[i - 1][j + 1] > grid[i][j]) {

            dp[i][j] = max(dp[i][j], 1 + dfs(i - 1, j + 1, n, m, dp, grid));

        }
        if (grid[i][j + 1] > grid[i][j]) {

            dp[i][j] = max(dp[i][j], 1 + dfs(i, j + 1, n, m, dp, grid));

        }
        if (i + 1 < n && grid[i + 1][j + 1] > grid[i][j]) {

            dp[i][j] = max(dp[i][j], 1 + dfs(i + 1, j + 1, n, m, dp, grid));

        }
        return dp[i][j];
    }
    int maxMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>>dp(n, vector<int>(m, -1));
        int ans = INT_MIN;
        for (int i = 0;i < n;i++) {
            ans = max(ans, dfs(i, 0, n, m, dp, grid));
        }
        return ans;
    }
};