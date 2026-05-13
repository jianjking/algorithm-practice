#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int ans = 0;
        for (int i = 0;i < m;i++) {
            for (int j = 1;j < n;j++) {
                int c = grid[j][i] - grid[j - 1][i];
                if (c < 0) {
                    ans += abs(c) + 1;
                    grid[j][i] += abs(c) + 1;
                }
            }
        }
        return ans;
    }
};