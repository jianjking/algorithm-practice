#include<iostream>
#include<vector>
#include<set>
using namespace std;

#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

class Solution {
public:
    std::vector<int> getSubarrayBeauty(std::vector<int>& nums, int k, int x) {
        using P = std::pair<int, int>;
        std::multiset<P> L, R; // L: 最小的 x 个；R: 其余

        auto push = [&](const P& p) {
            if ((int)L.size() < x) {
                L.insert(p);
            }
            else {
                auto itMaxL = std::prev(L.end());           // L 中最大
                if (p <= *itMaxL) {                         // 新元素应进入 L
                    R.insert(*itMaxL);                      // 把 L 的最大移到 R
                    L.erase(itMaxL);
                    L.insert(p);
                }
                else {
                    R.insert(p);
                }
            }
            };

        auto erase_one = [&](const P& p) {
            auto itL = L.find(p);
            if (itL != L.end()) {
                L.erase(itL);
                // 补齐 L 的规模（保持 L 有 x 个最小元素）
                if (!R.empty()) {
                    auto itMinR = R.begin();
                    L.insert(*itMinR);
                    R.erase(itMinR);
                }
            }
            else {
                auto itR = R.find(p);
                if (itR != R.end()) R.erase(itR);
                // 正常不需要额外操作
            }
            };

        const int n = (int)nums.size();
        std::vector<int> ans(n - k + 1);

        // 先预热 k-1 个
        for (int i = 0; i < k - 1; ++i) push({ nums[i], i });

        for (int i = k - 1; i < n; ++i) {
            push({ nums[i], i });                       // 插入右端点
            int v = L.empty() ? 0 : std::prev(L.end())->first; // 第 x 小
            ans[i - k + 1] = std::min(v, 0);         // 题意要求：非负取 0
            erase_one({ nums[i - k + 1], i - k + 1 }); // 删除左端点，滑窗右移
        }
        return ans;
    }
};
