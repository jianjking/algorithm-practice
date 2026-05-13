#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:

    long long findMinimumTime(vector<int>& strength, int k) {
        int n = strength.size();
        int m = 1 << n;
        const long long INF = (1LL << 60);
        vector<long long> dp(m, INF);
        dp[0] = 0;

        for (int mask = 0; mask < m; ++mask) {
            if (dp[mask] == INF) continue;
            int opened = __builtin_popcount((unsigned)mask);
            long long x = 1LL + 1LL * k * opened;           // µ±Ç° X
            for (int j = 0; j < n; ++j) if (!(mask & (1 << j))) {
                long long s = strength[j];
                long long cost = (s + x - 1) / x;           // ceil(s/x)
                int nmask = mask | (1 << j);
                dp[nmask] = min(dp[nmask], dp[mask] + cost);
            }
        }
        return dp[m - 1];
    }

};