#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void  f(vector<vector<int>>& grid, int i, int j) {
        int n = grid.size();
        int m = grid[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != 1) {
            return;
        }
        grid[i][j] = 0;
        f(grid, i + 1, j); f(grid, i, j + 1); f(grid, i - 1, j); f(grid, i, j - 1);

    }
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int ans = 0;
        for (int i = 0;i < m;i++) {
            if (grid[0][i])f(grid, 0, i);
            if (grid[n - 1][i])f(grid, n - 1, i);
        }
        for (int i = 0;i < n;i++) {
            if (grid[i][0])f(grid, i, 0);
            if (grid[i][m - 1])f(grid, i, m - 1);
        }

        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (grid[i][j])ans++;
            }
        }
        return ans;
    }
};