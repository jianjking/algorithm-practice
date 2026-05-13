#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int>num(m, 0);
        for (int i = 0;i < n;i++) {
            if (grid[i][0]) {
                for (int j = 0;j < m;j++)num[j] += grid[i][j];
            }
            else {
                for (int j = 0;j < m;j++) {
                    grid[i][j] ^= 1;
                    num[j] += grid[i][j];
                }
            }
        }
        for (int i = 0;i < m;i++) {
            if ((n + 1) / 2 > num[i])num[i] = 1;
            else num[i] = 0;
        }
        int ans = 0;
        for (int i = 0;i < n;i++) {
            int sum = 0;
            for (int j = 0;j < m;j++) {
                sum = (sum * 2) + (grid[i][j] ^ num[j]);
            }
            ans += sum;
        }
        return ans;
    }
};