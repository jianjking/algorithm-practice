#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    long long maxArea(vector<vector<int>>& coords) {
        int hx = INT_MIN, hn = INT_MAX;
        int nx = INT_MIN, nn = INT_MAX;
        long long ans = 0;

        // 用哈希表存 (min_y, max_y) 对应 x
        unordered_map<int, pair<int, int>> n;
        // 用哈希表存 (min_x, max_x) 对应 y
        unordered_map<int, pair<int, int>> h;

        for (auto& p : coords) {
            int a = p[0], b = p[1];
            hx = max(hx, a);
            hn = min(hn, a);
            nx = max(nx, b);
            nn = min(nn, b);

            // 更新 n[a]
            if (!n.count(a)) n[a] = { INT_MAX, INT_MIN };
            n[a].first = min(n[a].first, b);
            n[a].second = max(n[a].second, b);

            // 更新 h[b]
            if (!h.count(b)) h[b] = { INT_MAX, INT_MIN };
            h[b].first = min(h[b].first, a);
            h[b].second = max(h[b].second, a);
        }

        // 遍历活跃 x
        for (auto& [i, pr] : n) {
            int d = pr.second - pr.first;
            if (d > 0) {
                ans = max(ans, max(1LL * (i - hn) * d,
                    1LL * (hx - i) * d));
            }
        }

        // 遍历活跃 y
        for (auto& [i, pr] : h) {
            int d = pr.second - pr.first;
            if (d > 0) {
                ans = max(ans, max(1LL * (i - nn) * d,
                    1LL * (nx - i) * d));
            }
        }

        return ans == 0 ? -1 : ans;
    }
};
