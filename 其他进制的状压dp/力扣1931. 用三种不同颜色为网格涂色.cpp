#include<iostream>
#include<vector>
using namespace std;
class Solution {
    static const int MOD = 1000000007;

    // 从状态 s 中提取当前 bit 表示的位置的颜色（三进制）
    int getState(int s, int bit) {
        return (s / bit) % 3;
    }

    // 将状态 s 中 bit 位置的颜色设为 v，并返回新状态
    int setState(int s, int v, int bit) {
        int pre = getState(s, bit);
        return s + (v - pre) * bit;
    }

    // 递归生成第一行的所有合法配色状态
    void genFirst(int j, int s, int m, int bit, vector<int>& first) {
        if (j == m) {
            first.push_back(s);
            return;
        }
        int left = (j == 0 ? -1 : getState(s, bit / 3));
        for (int z = 0; z < 3; z++) {
            if (z != left) {
                genFirst(j + 1, setState(s, z, bit), m, bit * 3, first);
            }
        }
    }

    // 记忆化 DFS：从 (i,j) 位置，上一行状态为 s，计算染色方案数
    int dfsDP(int i, int j, int s,
        int n, int m,
        vector<vector<vector<int>>>& dp,
        int bit) {
        if (i == n) return 1;                   // 完成所有行
        if (j == m)                           // 换下一行
            return dfsDP(i + 1, 0, s, n, m, dp, 1);
        if (dp[i][j][s] != -1)                // 已计算过
            return dp[i][j][s];

        int up = (i == 0 ? -1 : getState(s, bit));
        int left = (j == 0 ? -1 : getState(s, bit / 3));
        long long ans = 0;

        for (int z = 0; z < 3; z++) {
            if (z != up && z != left) {
                ans = (ans + dfsDP(i, j + 1,
                    setState(s, z, bit),
                    n, m, dp, bit * 3)) % MOD;
            }
        }
        return dp[i][j][s] = int(ans);
    }

public:
    int colorTheGrid(int m, int n) {
        // 保证 m <= n，减少状态维度
        if (m > n) swap(m, n);

        // 计算三进制的最大状态数 3^m
        int S = 1;
        for (int i = 0; i < m; i++) S *= 3;

        // 生成第一行的所有合法状态
        vector<int> first;
        first.reserve(S);
        genFirst(0, 0, m, 1, first);

        // dp[i][j][s] = 从 (i,j) 且上一行状态为 s 开始的方案数
        vector dp(n, vector(m, vector<int>(S, -1)));

        long long ans = 0;
        // 枚举第一行状态，累加从 (0,0) 开始的方案数
        for (int s : first) {
            ans = (ans + dfsDP(1, 0, s, n, m, dp, 1)) % MOD;
        }
        return int(ans);
    }
};