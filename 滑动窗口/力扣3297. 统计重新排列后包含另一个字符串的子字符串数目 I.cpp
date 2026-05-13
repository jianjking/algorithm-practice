#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        unordered_map<char, int> cnt;
        for (char c : word2) cnt[c]++;

        int need = word2.size();     // 还缺多少个字符（含重复）
        int n = word1.size();
        long long sum = 0;
        int r = 0;

        for (int l = 0; l < n; ++l) {
            // 扩右边，直到当前窗口包含 word2 所有字符
            while (r < n && need > 0) {
                char c = word1[r];
                if (cnt.count(c)) {
                    if (cnt[c] > 0) need--;  // 补上一个真正缺的
                    cnt[c]--;                // 多的会变负数
                }
                r++;
            }

            // 如果已经满足条件，所有 [l..r-1], [l..r], ..., [l..n-1] 都合法
            if (need == 0) {
                sum += (long long)(n - r + 1);
            }

            // 收缩左边，把 word1[l] 移出窗口
            char c = word1[l];
            if (cnt.count(c)) {
                cnt[c]++;            // 还回去
                if (cnt[c] > 0) {    // 由 0 -> 1，表示又缺一个
                    need++;
                }
            }
        }
        return sum;
    }
};
