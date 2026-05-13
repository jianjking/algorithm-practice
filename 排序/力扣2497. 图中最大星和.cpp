#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        int n = vals.size();
        vector<vector<int>> graph(n);  // 不变：图结构
        for (auto& e : edges) {
            graph[e[0]].push_back(vals[e[1]]);  // ✅ 直接存邻居的值
            graph[e[1]].push_back(vals[e[0]]);  // ✅
        }

        int ans = INT_MIN;
        for (int i = 0; i < n; i++) {
            auto& v = graph[i];       // 现在 graph[i] 就是邻居值了
            int cnt = min(k, (int)v.size());
            if (cnt > 0) {
                nth_element(v.begin(), v.begin() + cnt, v.end(), greater<>());
            }

            int sum = vals[i];
            for (int j = 0; j < cnt; j++) {
                if (v[j] > 0) sum += v[j];  // ✅ 只加正值
            }

            ans = max(ans, sum);
        }

        return ans;
    }
};
