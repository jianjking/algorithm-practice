#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cstring>
using namespace std;
//哈希表做法
class Solution {
public:
    int countLargestGroup(int n) {
        map<int, int>graph;
        for (int i = 1;i <= n;i++) {
            int tmp = i;
            int ans = 0;
            while (tmp) {
                ans += tmp % 10;
                tmp /= 10;
            }
            graph[ans]++;
        }
        int max1 = INT_MIN;
        for (auto& p : graph) {
            max1 = max(max1, p.second);
        }
        int ans = 0;
        for (auto& p : graph) {
            if (p.second == max1)ans++;
        }
        return ans;
    }
    
};
//最优解数位dp牛牛牛
class Solution {
public:
    int countLargestGroup(int n) {
        string s = to_string(n);
        int m = s.size();
        vector memo(m, vector<int>(m * 9 + 1, -1));
        auto dfs = [&](this auto&& dfs, int i, int left, bool limit_high) -> int {
            if (i == m) {
                return left == 0;
            }
            if (!limit_high && memo[i][left] != -1) {
                return memo[i][left];
            }

            int hi = limit_high ? s[i] - '0' : 9; // 当前数位至多填 hi
            int res = 0;
            for (int d = 0; d <= min(hi, left); d++) { // 枚举当前数位填 d
                res += dfs(i + 1, left - d, limit_high && d == hi);
            }

            if (!limit_high) {
                memo[i][left] = res;
            }
            return res;
            };

        int max_cnt = 0, ans = 0;
        for (int target = 1; target <= m * 9; target++) { // 枚举目标数位和
            int cnt = dfs(0, target, true);
            if (cnt > max_cnt) {
                max_cnt = cnt;
                ans = 1;
            }
            else if (cnt == max_cnt) {
                ans++;
            }
        }
        return ans;
    }
};