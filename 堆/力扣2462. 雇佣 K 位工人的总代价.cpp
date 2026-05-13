#include<iostream>
#include<vector>
#include<set>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

struct Cmp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.second != b.second) return a.second < b.second; // 先按 cost 升序
        return a.first < b.first;                               // 再按 index 升序
    }
};

class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        using P = pair<int, int>; // {idx, cost}
        set<P, Cmp> com;
        long long ans = 0;
        int n = (int)costs.size();

        // 双指针：下一次该从哪里补位
        int l = 0, r = n - 1;

        // 先从左侧放最多 candidates 个
        for (int i = 0; i < candidates && l <= r; ++i) {
            com.insert({ l, costs[l] });
            ++l;
        }
        // 再从右侧放最多 candidates 个（避免与左侧重叠）
        for (int i = 0; i < candidates && l <= r; ++i) {
            com.insert({ r, costs[r] });
            --r;
        }

        for (int t = 0; t < k && !com.empty(); ++t) {
            auto it = com.begin();
            int idx = it->first;
            int cost = it->second;
            ans += cost;
            com.erase(it);

            // 根据弹出元素的 index 判断来自哪一侧，然后从对应侧补位
            if (idx < l) {
                // 来自左池
                if (l <= r) {
                    com.insert({ l, costs[l] });
                    ++l;
                }
            }
            else {
                // 来自右池
                if (l <= r) {
                    com.insert({ r, costs[r] });
                    --r;
                }
            }
        }
        return ans;
    }
};
