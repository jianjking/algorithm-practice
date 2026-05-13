#include<bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(string s, int k) {
        long long val = 0;   // 当前子序列的十进制值
        long long w = 1;     // 当前可选 1 的位权（2^bits），对长度有贡献的“已选位数”决定
        int ans = 0;         // 已选长度

        for (int i = (int)s.size() - 1; i >= 0; --i) {
            if (s[i] == '0') {
                // 0 不增值，必选，长度+1
                ans++;
            } else {
                // 若把这个 1 放在当前位权 w，不超过 k，就选
                if (val + w <= k) {
                    val += w;
                    ans++;
                }
            }
            // 位权只要还不超过 k，就安全地左移一位；
            // 一旦超过 k，再大的权重也加不进来了，保持饱和（等效于 cap 在 k+1）
            if (w <= k) w <<= 1;
        }
        return ans;
    }
};