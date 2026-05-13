#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int arrive(int i, vector<vector<int>>& grid, int n, int m) {
        int j = 0;
        while (j < n) {
            if (grid[j][i] == 1) {
                if (i + 1 == m || grid[j][i + 1] == -1)return -1;
                i++;
                j++;
            }
            else {
                if (i == 0 || grid[j][i - 1] == 1)return -1;
                j++;
                i--;
            }
        }
        return i;
    }
    vector<int> findBall(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int>ans(m, -1);
        for (int i = 0; i < m; i++) {
            ans[i] = arrive(i, grid, n, m);
        }
        return ans;
    }
};