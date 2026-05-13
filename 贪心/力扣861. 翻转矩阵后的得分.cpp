#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            if (grid[i][0])continue;
            for (int j = 0; j < m; j++) {
                grid[i][j] ^= 1;
            }
        }
        vector<int>cnt(m, 0);
        cnt[0] = n;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[j][i])cnt[i]++;
            }
            if (cnt[i] <= n / 2)cnt[i] = n - cnt[i];
        }
        int ans = 0;
        for (int i = m - 1; i >= 0; i--) {
            ans += cnt[i] * pow(2, m - 1 - i);
        }
        return ans;
    }
};