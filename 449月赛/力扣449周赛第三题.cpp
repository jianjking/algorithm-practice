#include<iostream>
#include<vector>
#include<deque>
using namespace std;
class Solution {
public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        vector g(n, vector<int>{});
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> cycle, chain;
        vector<uint8_t> vis(n);
        int cnt_v, cnt_e;

        auto dfs = [&](this auto&& dfs, int x) -> void {
            vis[x] = 1;
            cnt_v++;
            cnt_e += g[x].size();
            for (int y : g[x]) {
                if (!vis[y]) {
                    dfs(y);
                }
            }
            };

        for (int i = 0; i < n; i++) {
            if (vis[i]) {
                continue;
            }
            cnt_v = 0;
            cnt_e = 0;
            dfs(i);
            if (cnt_v * 2 == cnt_e) { // 环
                cycle.push_back(cnt_v);
            }
            else if (cnt_e > 0) { // 链，但不考虑孤立点
                chain.push_back(cnt_v);
            }
        }

        long long ans = 0;
        int cur = n;

        auto f = [&](int sz, bool is_cycle) -> void {
            int l = cur - sz + 1, r = cur;
            for (int i = l; i < r - 1; i++) {
                ans += 1LL * i * (i + 2);
            }
            ans += 1LL * r * (r - 1);
            if (is_cycle) {
                ans += 1LL * l * (l + 1);
            }
            cur -= sz;
            };

        ranges::sort(cycle);
        for (int sz : cycle) {
            f(sz, true);
        }

        ranges::sort(chain, ranges::greater());
        for (int sz : chain) {
            f(sz, false);
        }

        return ans;
    }
};