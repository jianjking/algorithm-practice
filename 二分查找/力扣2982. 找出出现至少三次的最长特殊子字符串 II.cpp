#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maximumLength(std::string s) {
        const int n = static_cast<int>(s.size());
        // 题目保证 s 由小写字母组成；用 26 桶比 unordered_map 更快更稳
        std::vector<std::vector<int>> runs(26);

        // RLE：按字符把每段连续相同字符的长度收集起来
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) ++j;
            runs[s[i] - 'a'].push_back(j - i);
            i = j;
        }

        int res = -1;

        for (int c = 0; c < 26; ++c) {
            std::vector<int>& vec = runs[c];
            if (vec.empty()) continue;

            // 小优化1：如果该字符总出现次数都不到3，连 L=1 都不可能
            long long total = 0;
            int mx = 0;
            for (size_t k = 0; k < vec.size(); ++k) {
                total += vec[k];
                if (vec[k] > mx) mx = vec[k];
            }
            if (total < 3) continue;

            // L 的上界既不能超过 n-2（出现≥3次的必要条件），也不能超过该字符的最大段长
            int lo = 1;
            int hi = std::min(n - 2, mx);
            while (lo <= hi) {
                int mid = lo + ((hi - lo) >> 1); // 猜测的 special 子串长度 L
                long long cnt = 0;

                // 统计：所有该字符的连续段中，长度恰为 mid 的子串总出现次数
                for (size_t k = 0; k < vec.size(); ++k) {
                    int x = vec[k];
                    if (x >= mid) {
                        cnt += (x - mid + 1); // 允许重叠
                        if (cnt >= 3) break;  // 提前剪枝
                    }
                }

                if (cnt >= 3) {           // mid 可行 → 尝试更大
                    if (mid > res) res = mid;
                    lo = mid + 1;
                }
                else {                  // mid 不可行 → 缩小
                    hi = mid - 1;
                }
            }
        }
        return res;
    }
};
