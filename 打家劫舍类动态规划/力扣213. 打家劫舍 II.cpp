#include<iostream>
#include<vector>
using namespace std;
class Solution {

public:
    int best(vector<int>& nums, int l, int r) {
        if (l > r)return 0;
        if (l == r)return nums[l];
        if (r == l + 1)return max(nums[l], nums[l + 1]);
        int prepre = nums[l];
        int ans = INT_MIN;
        int pre = max(nums[l], nums[l + 1]);
        for (int i = l + 2;i <= r;i++) {
            int cur = max(max(nums[i], prepre + nums[i]), pre);
            ans = max(ans, cur);
            prepre = pre;
            pre = cur;
        }
        return ans;
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        return max(nums[0] + best(nums, 2, n - 2), best(nums, 1, n - 1));
    }
};