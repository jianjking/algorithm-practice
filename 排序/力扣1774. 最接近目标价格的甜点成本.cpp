#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using namespace std;
class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int n = baseCosts.size(), m = toppingCosts.size();
        // 1. 用命名递归函数枚举所有可能的 toppingSum
        vector<int> sums;
        sums.reserve(pow(3, m));
        dfsToppings(0, 0, toppingCosts, sums);

        // 2. 去重并排序
        sort(sums.begin(), sums.end());
        sums.erase(unique(sums.begin(), sums.end()), sums.end());

        // 3. 对每个 baseCost，二分找最接近 target-base 的 toppingSum
        int ans = baseCosts[0] + sums[0];  // 随便初始化一个合法解
        for (int b : baseCosts) {
            int want = target - b;
            auto it = lower_bound(sums.begin(), sums.end(), want);
            // 检查 it（>= want）和它前面的一个（< want）
            if (it != sums.end()) {
                updateAns(ans, b + *it, target);
            }
            if (it != sums.begin()) {
                --it;
                updateAns(ans, b + *it, target);
            }
        }
        return ans;
    }

private:
    // 递归枚举：对 toppingCosts[idx...] 做 0/1/2 份选择
    void dfsToppings(int idx, int cur,
        const vector<int>& toppingCosts,
        vector<int>& sums) {
        if (idx == (int)toppingCosts.size()) {
            sums.push_back(cur);
            return;
        }
        // 0 份
        dfsToppings(idx + 1, cur, toppingCosts, sums);
        // 1 份
        dfsToppings(idx + 1, cur + toppingCosts[idx], toppingCosts, sums);
        // 2 份
        dfsToppings(idx + 1, cur + 2 * toppingCosts[idx], toppingCosts, sums);
    }

    // 比较并更新最优解：距离更小 or 距离相同选成本更小
    void updateAns(int& ans, int cost, int target) {
        int d1 = abs(cost - target);
        int d2 = abs(ans - target);
        if (d1 < d2 || (d1 == d2 && cost < ans)) {
            ans = cost;
        }
    }
};
