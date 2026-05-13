#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // 行前缀：row[i][j+1] = 第 i 行前 j+1 个元素之和
        vector<vector<int>> row(n, vector<int>(m + 1, 0));
        // 列前缀：col[i+1][j] = 第 j 列前 i+1 个元素之和
        vector<vector<int>> col(n + 1, vector<int>(m, 0));
        // 主对角线前缀：diag1[i+1][j+1] = grid[i][j] + diag1[i][j]
        vector<vector<int>> diag1(n + 1, vector<int>(m + 1, 0));
        // 反对角线前缀：diag2[i+1][j] = grid[i][j] + diag2[i][j+1]
        vector<vector<int>> diag2(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                row[i][j + 1] = row[i][j] + grid[i][j];
                col[i + 1][j] = col[i][j] + grid[i][j];
                diag1[i + 1][j + 1] = diag1[i][j] + grid[i][j];
                diag2[i + 1][j] = diag2[i][j + 1] + grid[i][j];
            }
        }

        auto rowSum = [&](int r, int L, int R) {
            return row[r][R + 1] - row[r][L];
            };
        auto colSum = [&](int c, int T, int B) {
            return col[B + 1][c] - col[T][c];
            };
        auto mainDiagSum = [&](int i, int j, int k) { // 左上(i,j)，边长k
            return diag1[i + k][j + k] - diag1[i][j];
            };
        auto antiDiagSum = [&](int i, int j, int k) { // 右上(i, j+k-1) 到 左下(i+k-1, j)
            return diag2[i + k][j] - diag2[i][j + k];
            };

        for (int k = min(n, m); k >= 2; --k) { // 从大到小，找到就返回
            for (int i = 0; i + k <= n; ++i) {
                for (int j = 0; j + k <= m; ++j) {
                    int target = rowSum(i, j, j + k - 1);
                    if (mainDiagSum(i, j, k) != target) continue;
                    if (antiDiagSum(i, j, k) != target) continue;

                    bool ok = true;
                    for (int r = i; r < i + k && ok; ++r)
                        if (rowSum(r, j, j + k - 1) != target) ok = false;
                    for (int c = j; c < j + k && ok; ++c)
                        if (colSum(c, i, i + k - 1) != target) ok = false;

                    if (ok) return k;
                }
            }
        }
        return 1; // 至少 1x1
    }
};
