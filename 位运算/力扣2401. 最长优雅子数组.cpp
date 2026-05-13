#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size(), status = 0, ans = 1;
        for (int l = 0, r = 0; r < n; ++l) {
            while (r < n && ((status & nums[r]) == 0)) {
                status |= nums[r++];
            }
            ans = max(ans, r - l);
            status &= ~nums[l];  // 将 nums[l] 的位从 status 中移除
        }
        return ans;
    }
};
