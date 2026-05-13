#include<iostream>
#include<vector>
#include<array>
using namespace std;

/*
  问题模型：
  - 给定一棵以 0 号节点为根的树，每个节点 x 有两个属性：
      present[x]：买入成本
      future[x] : 卖出收益
  - 如果一个节点的父节点被买入，则该节点买入时享受 50% 折扣（cost = present[x] / 2）。
  - 总预算为 B，需要在整棵树上选择哪些节点买 / 不买，以最大化总净利润：
      对于已买节点 x，净利润 = future[x] - 实际成本；未买节点利润为 0。
*/

/*
  DP 设计：
  对于每个子树根 x，我们定义一个函数 dfs(x)，返回一个大小为 (B+1)×2 的数组 f，
  其中：
    - f[j][0] 表示：在子树 x 中，剩余预算 j，且 x 的父节点 **未** 买入（k=0）时的最大总利润。
      此时 x 如果买，要付 full price = present[x]。
    - f[j][1] 表示：在子树 x 中，剩余预算 j，且 x 的父节点 **已** 买入（k=1）时的最大总利润。
      此时 x 如果买，要付 half price = present[x] / 2。
  最终答案是 dfs(0)[B][0]，因为根节点没有父节点，视作“父未买”。
*/

class Solution {
public:
    int maxProfit(int n,
        const vector<int>& present,
        const vector<int>& future,
        const vector<vector<int>>& hierarchy,
        int budget)
    {
        _n = n;
        _B = budget;
        _present = present;
        _future = future;

        // 构建树的邻接表：children[u] 存放所有以 u 为父的子节点 v
        _children.assign(n, {});
        for (auto& e : hierarchy) {
            int u = e[0] - 1;    // 题目编号从 1 开始，转换到 0-base
            int v = e[1] - 1;
            _children[u].push_back(v);
        }

        // 从根节点 0 开始做 DFS DP
        auto F = dfs(0);

        // 根节点没有父节点，视作 k=0（父未买），取预算 B 下的最优值
        return F[_B][0];
    }

private:
    int _n, _B;
    vector<int> _present, _future;
    vector<vector<int>> _children;

    // 对子树 x 做 DP，返回 (B+1)×2 的表 f
    vector<array<int, 2>> dfs(int x) {
        // ========== 第 1 步：合并所有子节点的 DP ==========
        // sub_dp[j][k] 表示：到目前为止已经合并的子树（尚未处理 x 自己），
        // 在剩余预算 j、父状态 k 下的最大利润。
        vector<array<int, 2>> sub_dp(_B + 1, { 0, 0 });

        // 遍历 x 的每个直接子节点 y，将其视为一个“物品集”合并进来
        for (int y : _children[x]) {
            // 先递归，得到子树 y 的 DP 表 fy
            auto fy = dfs(y);

            // new_dp 用来存放合并 y 之后的结果
            vector<array<int, 2>> new_dp(_B + 1, { 0, 0 });

            // 做「多维背包」：在总预算 j 下，把 j 分成两部分：
            //   (j - t) 给之前的子树们（sub_dp[j-t][k]）
            //   t       给当前子树 y （fy[t][k]）
            for (int j = 0; j <= _B; j++) {
                for (int t = 0; t <= j; t++) {
                    for (int k = 0; k < 2; k++) {
                        new_dp[j][k] = max(
                            new_dp[j][k],
                            sub_dp[j - t][k] + fy[t][k]
                        );
                    }
                }
            }

            // 合并完 y 后，更新 sub_dp
            sub_dp.swap(new_dp);
        }

        // ========== 第 2 步：考虑 x 自身“买 or 不买” ==========
        // 准备返回的 DP 表 f[j][k]
        vector<array<int, 2>> f(_B + 1, { 0, 0 });

        // 对每个预算 j 和父状态 k，计算 f[j][k]
        for (int j = 0; j <= _B; j++) {
            for (int k = 0; k < 2; k++) {
                // 计算买入 x 的实际成本：父未买(full) or 已买(half)
                int cost = _present[x] / (k + 1);

                // —— 情况 1：不买 x —— 
                // 此时 x 本身不贡献利润，子树都以“父状态 = 0”来做
                int bestNoBuy = sub_dp[j][0];

                // —— 情况 2：买 x ——
                // 需要预算足够 j >= cost
                // 买入后，净利润 = future[x] - cost
                // 子树都以“父状态 = 1”来做
                int bestBuy = INT_MIN;
                if (j >= cost) {
                    bestBuy = sub_dp[j - cost][1]      // 子树贡献
                        + (_future[x] - cost);  // 自身净利润
                }

                // 取两者最大
                f[j][k] = max(bestNoBuy, bestBuy);
            }
        }

        // 返回当前子树 x 的 DP 表
        return f;
    }
};
