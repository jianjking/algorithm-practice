#include<Iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        int n = packages.size();
        sort(packages.begin(), packages.end());
        vector<long long>sum(n + 1, 0);
        for (int i = 1;i <= n;i++) {
            sum[i] = sum[i - 1] + packages[i - 1];
        }
        long long ans = LLONG_MAX;
        int m = boxes.size();
        for (int i = 0;i < m;i++) {
            long long total = 0;
            auto pt = packages.begin();
            sort(boxes[i].begin(), boxes[i].end());
            if (packages.back() > boxes[i].back()) {
                continue;
            }
            for (int j = 0;j < boxes[i].size();j++) {
                auto pr = upper_bound(packages.begin(), packages.end(), boxes[i][j]);
                if (pr == packages.begin()) {
                    continue;
                }
                pr--;
                total = (total + (pr - pt + 1) * boxes[i][j] - sum[pr - packages.begin() + 1] + sum[pt - packages.begin()]);
                pt = pr + 1;
            }
            ans = min(ans, total);
        }
        return ans == LLONG_MAX ? -1 : ans % mod;
    }
};