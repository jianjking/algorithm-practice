#include<iostream>
#include<vector>
using namespace std;
const int INF = INT_MAX / 4;
class Solution {
public:
    int dfs(int i, int n, int target, int last, vector<int>& houses, vector<vector<int>>& cost, vector<vector<vector<int>>>& dp) {
        if (target < 0)return INT_MAX / 2;
        if (i == -1) {
            if (target > 0)return INT_MAX / 2;
            return   0;
        }
        int& res = dp[i][target][last];
        if (res != -1)return res;
        res = INT_MAX / 2;
        if (houses[i] != 0) {
            if (houses[i] == last) {
                res = min(res, dfs(i - 1, n, target, last, houses, cost, dp));
            }
            else {
                res = min(res, dfs(i - 1, n, target - 1, houses[i], houses, cost, dp));
            }
        }
        else {
            for (int j = 1; j <= n; j++) {
                if (j == last) {
                    res = min(res, cost[i][j - 1] + dfs(i - 1, n, target, last, houses, cost, dp));
                }
                else {
                    res = min(res, cost[i][j - 1] + dfs(i - 1, n, target - 1, j, houses, cost, dp));
                }
            }
        }
        return res;
    }


        // 与你的 dfs 语义一致：从右往左滚动
        int f1(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
            // dp[j][c]: 右侧( i+1..m-1 ) 已处理完成时，街区数=j，右边相邻颜色= c 的最小代价
            vector<vector<int>> dp(target + 1, vector<int>(n + 1, INF));
            dp[0][0] = 0;  // 最右侧为空，0 个街区，右边颜色=0

            for (int i = m - 1; i >= 0; --i) {  // 关键：从右往左
                vector<vector<int>> cur(target + 1, vector<int>(n + 1, INF));

                // 预处理 dp[j-1][*] 的前后缀最小，供 “c != x” 时 O(1) 查询
                vector<vector<int>> pre(target + 1, vector<int>(n + 2, INF));
                vector<vector<int>> suf(target + 1, vector<int>(n + 2, INF));
                for (int j = 1; j <= target; ++j) {
                    int mn = INF;
                    for (int c = 1; c <= n; ++c) {
                        mn = min(mn, dp[j - 1][c]);
                        pre[j][c] = mn;
                    }
                    mn = INF;
                    for (int c = n; c >= 1; --c) {
                        mn = min(mn, dp[j - 1][c]);
                        suf[j][c] = mn;
                    }
                }

                if (houses[i] != 0) {
                    int h = houses[i];
                    for (int j = 0; j <= target; ++j) {
                        // 不开新街区（右边颜色与当前相同）
                        if (dp[j][h] < INF) cur[j][h] = min(cur[j][h], dp[j][h]);
                        // 开新街区（右边颜色 != h）
                        if (j >= 1) {
                            int best = INF;
                            if (h - 1 >= 1) best = min(best, pre[j][h - 1]);
                            if (h + 1 <= n) best = min(best, suf[j][h + 1]);
                            if (best < INF) cur[j][h] = min(cur[j][h], best);
                        }
                    }
                }
                else {
                    // 未涂色：枚举当前要涂成的颜色 z
                    for (int j = 0; j <= target; ++j) {
                        for (int z = 1; z <= n; ++z) {
                            // 不开新街区（右边颜色 == z）
                            if (dp[j][z] < INF) {
                                cur[j][z] = min(cur[j][z], dp[j][z] + cost[i][z - 1]);
                            }
                            // 开新街区（右边颜色 != z）
                            if (j >= 1) {
                                int best = INF;
                                if (z - 1 >= 1) best = min(best, pre[j][z - 1]);
                                if (z + 1 <= n) best = min(best, suf[j][z + 1]);
                                if (best < INF) {
                                    cur[j][z] = min(cur[j][z], best + cost[i][z - 1]);
                                }
                            }
                        }
                    }
                }

                dp.swap(cur);
            }

            int ans = INF;
            for (int c = 1; c <= n; ++c) ans = min(ans, dp[target][c]);
            return ans >= INF ? -1 : ans;
        }

    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        vector<vector<vector<int>>>dp(m, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        int ans = dfs(m - 1, n, target, 0, houses, cost, dp);
        return ans >= INT_MAX / 4 ? -1 : ans;
    }
};
