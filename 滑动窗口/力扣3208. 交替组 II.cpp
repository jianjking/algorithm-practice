#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n = colors.size();
        // 双倍化数组，方便模拟环
        colors.insert(colors.end(), colors.begin(), colors.begin() + n);

        int ans = 0;
        int l = 0, r = 0;
        while (l < n) {
            // 把 r 扩到最长的交替段（长度上限 n）
            while (r - l + 1 < n &&
                r + 1 < 2 * n &&
                colors[r] != colors[r + 1]) {
                r++;
            }
            int len = r - l + 1;
            if (len >= k) {
                // 计算这一段里所有合法起点的区间 [l … r-k+1]
                int maxStart = r - k + 1;
                // 限制到原数组下标 ≤ n-1
                int lastStart = min(maxStart, n - 1);
                if (lastStart >= l) {
                    ans += (lastStart - l + 1);
                }
                // 跳过刚才统计过的起点们
                l = maxStart + 1;
                r = max(r, l);
            }
            else {
                // 长度不够，直接从下一个点再试
                l = r + 1;
                r = l;
            }
        }
        return ans;
    }
};
