#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int m = intervals.size(), n = queries.size();
        // 1) 离线查询
        vector<pair<int, int>> qs(n);
        for (int i = 0; i < n; ++i)
            qs[i] = { queries[i], i };
        sort(qs.begin(), qs.end());
        sort(intervals.begin(), intervals.end(),
            [](auto& a, auto& b) { return a[0] < b[0]; });

        // 2) min-heap of (length, end)
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > heap;

        vector<int> ans(n, -1);
        int j = 0;
        for (auto& [q, qi] : qs) {
            // 把所有 start <= q 的区间 push 进去
            while (j < m && intervals[j][0] <= q) {
                int len = intervals[j][1] - intervals[j][0] + 1;
                int end = intervals[j][1];
                heap.emplace(len, end);
                ++j;
            }
            // 弹出所有 end < q 的“过期”区间
            while (!heap.empty() && heap.top().second < q) {
                heap.pop();
            }
            // 堆顶（若非空）就是最小长度
            if (!heap.empty())
                ans[qi] = heap.top().first;
        }
        return ans;
    }
};
