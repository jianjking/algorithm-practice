#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        int  n = nums.size();
        if (n == 1)return nums[0];
        if (n == 2)return max(nums[0], nums[1]);
        int prepre = nums[0];
        int pre = max(nums[0], nums[1]);
        int ans = INT_MIN;
        for (int i = 2;i < n;i++) {
            int cur = max(pre, max(nums[i], nums[i] + prepre));
            ans = max(ans, cur);
            prepre = pre;
            pre = cur;
        }
        return ans;
    }
};