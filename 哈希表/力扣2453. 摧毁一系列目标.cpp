#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    int destroyTargets(vector<int>& nums, int space) {
        unordered_map<int, int> cnt;          // 统计每个余数出现次数
        cnt.reserve(nums.size() * 2);        // 小优化：减少rehash
        cnt.max_load_factor(0.7f);

        for (int x : nums) {
            ++cnt[x % space];
        }

        int best = 0;                        // 当前最大可消灭数
        int ans = INT_MAX;                  // 同分时取更小的数
        for (int x : nums) {
            int c = cnt[x % space];
            if (c > best || (c == best && x < ans)) {
                best = c;
                ans = x;
            }
        }
        return ans;
    }
};
