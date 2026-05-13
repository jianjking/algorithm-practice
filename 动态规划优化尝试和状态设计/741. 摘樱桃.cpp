#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int a, int b, int c, int n, vector<vector<vector<int>>>& dp, vector<vector<int>>& grid) {
        int d = a + b - c;
        if (a == n || b == n || c == n || d == n || grid[a][b] == -1 || grid[c][d] == -1)return -1;
        if (a == n - 1 && b == n - 1 && c == n - 1 && d == n - 1)return grid[a][b];
        if (dp[a][b][c] != -2)return dp[a][b][c];
        int cur = (a == c && b == d) ? grid[a][b] : grid[a][b] + grid[c][d];
        int nxt = -1;
        nxt = max(nxt, dfs(a + 1, b, c, n, dp, grid));
        nxt = max(nxt, dfs(a + 1, b, c + 1, n, dp, grid));
        nxt = max(nxt, dfs(a, b + 1, c, n, dp, grid));
        nxt = max(nxt, dfs(a, b + 1, c + 1, n, dp, grid));
        if (nxt == -1) {
            dp[a][b][c] = -1;
            return -1;
        }
        else {
            dp[a][b][c] = cur + nxt;
        }
        return cur + nxt;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<vector<int>>>dp(n, vector<vector<int>>(n, vector<int>(n, -2)));
        return dfs(0, 0, 0, n, dp, grid) == -1 ? 0 : dfs(0, 0, 0, n, dp, grid);
    }
};