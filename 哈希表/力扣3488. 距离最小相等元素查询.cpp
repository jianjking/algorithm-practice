#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        // 1. 建立 值 → 下标列表 的映射
        unordered_map<int, vector<int>> mp;
        mp.reserve(n * 2);
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        // 2. 把每个列表排序（方便二分）
        for (auto& p : mp) {
            auto& v = p.second;
            sort(v.begin(), v.end());
        }

        int m = queries.size();
        vector<int> ans(m);
        // 3. 对每个查询
        for (int qi = 0; qi < m; qi++) {
            int a = queries[qi];
            int x = nums[a];
            auto& lst = mp[x];      // 已排序的所有下标列表

            // 如果仅有一次出现，直接 -1
            if (lst.size() <= 1) {
                ans[qi] = -1;
                continue;
            }

            // 1) 找到自己在 lst 中的位置 pos
            int pos = lower_bound(lst.begin(), lst.end(), a) - lst.begin();
            // （肯定有 lst[pos]==a）

            // 2) 右侧下一个
            int posR = (pos + 1) % lst.size();
            int jR = lst[posR];
            int distR = (jR - a + n) % n;    // 顺时针距离

            // 3) 左侧上一个
            int posL = (pos - 1 + (int)lst.size()) % lst.size();
            int jL = lst[posL];
            int distL = (a - jL + n) % n;    // 逆时针距离

            ans[qi] = min(distR, distL);
        }

        return ans;
    }
};