#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool dfs(int i, int j, vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        if (i<0 || j<0 || i>=n || j>=m || grid2[i][j] == 0)return true;
        bool a = true;
        if (grid1[i][j] == 0)a= false;
        grid2[i][j] = 0;
        bool a1 = dfs(i + 1, j, grid1, grid2);
        bool a2 = dfs(i, j + 1, grid1, grid2);
            bool a3 = dfs(i - 1, j, grid1, grid2);
        bool a4=dfs(i, j - 1, grid1, grid2);
       return a&&a1&&a2&&a3&&a4;
    }
    int ans;
    int n;
    int m;
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
         n = grid1.size();
        ans = 0;
         m = grid1[0].size();
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (grid2[i][j] == 1) {
                    if (dfs(i, j, grid1, grid2))ans++;
                }
            }
        }
        return ans;
    }
};