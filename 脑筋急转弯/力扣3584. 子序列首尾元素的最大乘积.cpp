#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        long long ans = LLONG_MIN;
        int mn = INT_MAX, mx = INT_MIN;
        for (int i = m - 1; i < nums.size(); i++) {
            // 维护左边 [0,i-m+1] 中的最小值和最大值
            int y = nums[i - m + 1];
            mn = min(mn, y);
            mx = max(mx, y);
            // 枚举右
            long long x = nums[i];
            ans = max({ ans, x * mn, x * mx });
        }
        return ans;
    }
};