#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<long long>>>dp(n, vector<vector<long long>>(m, vector<long long>(2, INT_MIN)));
        dp[0][0][0] = grid[0][0];
        dp[0][0][1] = grid[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dp[i][j][1] == INT_MIN)dp[i][j][1] = INT_MAX / 2;
                if (i - 1 >= 0) {
                    dp[i][j][0] = max(grid[i][j] * dp[i - 1][j][1], grid[i][j] * dp[i - 1][j][0]);
                    dp[i][j][1] = min(grid[i][j] * dp[i - 1][j][1], grid[i][j] * dp[i - 1][j][0]);
                }
                if (j - 1 >= 0) {
                    dp[i][j][0] = max({ dp[i][j][0],grid[i][j] * dp[i][j - 1][1], grid[i][j] * dp[i][j - 1][0] });

                    dp[i][j][1] = min({ dp[i][j][1],grid[i][j] * dp[i][j - 1][1], grid[i][j] * dp[i][j - 1][0] });
                }
            }
        }
        return dp[n - 1][m - 1][0] >= 0 ? dp[n - 1][m - 1][0] % mod : -1;
    }
};