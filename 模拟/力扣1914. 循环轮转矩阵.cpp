#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        int t = min(n, m) / 2;
        for (int z = 0; z < t; z++) {
            int i = z;
            int j = z;
            for (int x = 0; x < k % (2 * ((n - 2 * z) + (m - 2 * z)) - 4); x++) {
                int pre = grid[i][j + 1];
                while (i < n - z) {
                    int tmp = pre;
                    pre = grid[i][j];
                    grid[i][j] = tmp;
                    i++;
                }
                i--;
                j++;
                while (j < m - z) {
                    int tmp = pre;
                    pre = grid[i][j];
                    grid[i][j] = tmp;
                    j++;
                }
                j--;
                i--;
                while (i >= z) {
                    int tmp = pre;
                    pre = grid[i][j];
                    grid[i][j] = tmp;
                    i--;
                }
                i++;
                j--;
                while (j > z) {
                    int tmp = pre;
                    pre = grid[i][j];
                    grid[i][j] = tmp;
                    j--;
                }
            }
        }
        return grid;
    }
};