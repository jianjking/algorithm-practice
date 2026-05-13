#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long maximumTotalCost(vector<int>& a) {
        int n = a.size();
        vector<long long> memo(n, LLONG_MIN); // LLONG_MIN 表示没有计算过
        auto dfs = [&](auto&& dfs, int i) -> long long {
            if (i < 0) {
                return 0;
            }
            if (i == 0) {
                return a[0];
            }
            auto& res = memo[i]; // 注意这里是引用
            if (res != LLONG_MIN) { // 之前计算过
                return res;
            }
            return res = max(dfs(dfs, i - 1) + a[i], dfs(dfs, i - 2) + a[i - 1] - a[i]);
        };
        return dfs(dfs, n - 1);
    }
};
