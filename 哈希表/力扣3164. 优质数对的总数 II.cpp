#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> cnt;  // 统计 nums2 里出现次数
        for (int x : nums2) cnt[x]++;

        long long ans = 0;
        for (int x : nums1) {
            // 枚举 x 的所有因子
            for (int d = 1; d * d <= x; d++) {
                if (x % d == 0) {
                    // d 是因子
                    if (d % k == 0 && cnt.count(d / k)) {
                        ans += cnt[d / k];
                    }
                    int d2 = x / d;
                    if (d2 != d) { // 避免平方因子重复算
                        if (d2 % k == 0 && cnt.count(d2 / k)) {
                            ans += cnt[d2 / k];
                        }
                    }
                }
            }
        }
        return ans;
    }
};
