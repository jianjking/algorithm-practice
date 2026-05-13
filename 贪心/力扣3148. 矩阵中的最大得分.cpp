#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        const int NEG = INT_MIN / 4;

        // suf[i][j]: [i..n-1][j..m-1] 的最大值；多开一圈做边界
        vector<vector<int>> suf(n + 1, vector<int>(m + 1, NEG));
        int ans = INT_MIN;

        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int bestFuture = max(suf[i + 1][j], suf[i][j + 1]);
                if (bestFuture != NEG) { // 说明右/下存在可达格子 ⇒ 至少移动一次
                    ans = max(ans, bestFuture - grid[i][j]);
                }
                suf[i][j] = max({ grid[i][j], suf[i + 1][j], suf[i][j + 1] });
            }
        }

        // 如果是 1x1 网格，没有任何可走步，按题意一般返回 0（或题面规定）
        if (ans == INT_MIN) return 0;
        return ans;
    }
};
