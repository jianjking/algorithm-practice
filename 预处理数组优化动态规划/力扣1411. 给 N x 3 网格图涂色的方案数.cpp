#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
    static constexpr int mod = 1000000007;

public:
    int numOfWays(int n) {
        // 预处理出所有满足条件的 type
        vector<int> types;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (i != j && j != k) {
                        // 只要相邻的颜色不相同就行
                        // 将其以十进制的形式存储
                        types.push_back(i * 9 + j * 3 + k);
                    }
                }
            }
        }
        int type_cnt = types.size();
        // 预处理出所有可以作为相邻行的 type 对
        vector<vector<int>> related(type_cnt, vector<int>(type_cnt));
        for (int i = 0; i < type_cnt; ++i) {
            // 得到 types[i] 三个位置的颜色
            int x1 = types[i] / 9, x2 = types[i] / 3 % 3, x3 = types[i] % 3;
            for (int j = 0; j < type_cnt; ++j) {
                // 得到 types[j] 三个位置的颜色
                int y1 = types[j] / 9, y2 = types[j] / 3 % 3, y3 = types[j] % 3;
                // 对应位置不同色，才能作为相邻的行
                if (x1 != y1 && x2 != y2 && x3 != y3) {
                    related[i][j] = 1;
                }
            }
        }
        // 递推数组
        vector<vector<int>> f(n + 1, vector<int>(type_cnt));
        // 边界情况，第一行可以使用任何 type
        for (int i = 0; i < type_cnt; ++i) {
            f[1][i] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < type_cnt; ++j) {
                for (int k = 0; k < type_cnt; ++k) {
                    // f[i][j] 等于所有 f[i - 1][k] 的和
                    // 其中 k 和 j 可以作为相邻的行
                    if (related[k][j]) {
                        f[i][j] += f[i - 1][k];
                        f[i][j] %= mod;
                    }
                }
            }
        }
        // 最终所有的 f[n][...] 之和即为答案
        int ans = 0;
        for (int i = 0; i < type_cnt; ++i) {
            ans += f[n][i];
            ans %= mod;
        }
        return ans;
    }
};
