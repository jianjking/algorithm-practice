#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

/*
 * 题意：m×n 的 0/1 矩阵，每次“点击” (i,j) 会翻转它自己以及上下左右（越界忽略）。
 * 问最少点击几次能把矩阵变成全 0；无解返回 -1。
 *
 * 思路（核心）：把矩阵状态压成一个 bitmask（整数），对“状态图”做 BFS。
 * - 状态：一个 int（最多 3×3=9 位），第 k 位表示第 k 个格子的 0/1。
 * - 边：点击某个格子 v，会把状态按位异或一个“翻转掩码” flip[v]。
 * - BFS：每层表示“多点一次”，第一次遇到 0 就是最短步数。
 *
 * 复杂度：
 * - 状态数 ≤ 2^(m*n)（题目 m,n ≤ 3，最多 512 个状态）
 * - 每个状态枚举 m*n 次点击，单次转移 O(1) ⇒ 总时间 O(m*n * 2^(m*n))
 * - 空间 O(2^(m*n))
 */

class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        // 把二维坐标映射到一维下标 [0, m*n)
        auto id = [n](int i, int j) {
            return i * n + j;
            };

        // 1) 计算起始状态 start：把所有 1 的格子置位
        int start = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j]) {
                    start |= (1 << id(i, j));
                }
            }
        }
        if (start == 0) return 0; // 已经是全 0，0 步

        // 2) 预处理每个格子的“翻转掩码” flip[v]
        //    点击 v = (i,j) 时，会翻转 (i,j) 以及上下左右（若在界内）
        const int dirs[5][2] = { {-1,0},{1,0},{0,-1},{0,1},{0,0} }; // 上下左右 + 自身
        vector<int> flip(m * n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int mask = 0;
                for (auto& d : dirs) {
                    int x = i + d[0], y = j + d[1];
                    if (0 <= x && x < m && 0 <= y && y < n) {
                        mask |= (1 << id(x, y));
                    }
                }
                flip[id(i, j)] = mask;
            }
        }

        // 3) BFS：队列里放“状态”（bitmask），按层推进
        //    visited 用 char 节省内存；总状态数是 1<<(m*n)
        int totalStates = 1 << (m * n);
        vector<char> visited(totalStates, 0);
        queue<int> q;

        visited[start] = 1;
        q.push(start);

        int step = 0; // 当前已经点击的次数（层数）

        while (!q.empty()) {
            ++step;                // 进入下一层：多点一次
            int sz = q.size();
            while (sz--) {
                int cur = q.front(); q.pop();

                // 枚举这一步点击哪个格子 v
                for (int v = 0; v < m * n; ++v) {
                    // 状态转移：点击 v 相当于 cur ^ flip[v]
                    int nxt = cur ^ flip[v];

                    // 命中全 0，立刻返回当前步数（BFS 保证最短）
                    if (nxt == 0) return step;

                    if (!visited[nxt]) {
                        visited[nxt] = 1;
                        q.push(nxt);
                    }
                }
            }
        }

        // BFS 穷尽也没到全 0，说明无解
        return -1;
    }
};
