#include<iostream>
#include<vector>

#include <algorithm>
using namespace std;

class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        int n = nums.size();
        int x = nums[n / 2];
        // ´«Í³ lower_bound/upper_bound
        auto lb = lower_bound(nums.begin(), nums.end(), x);
        auto ub = upper_bound(nums.begin(), nums.end(), x);
        int max_cnt = ub - lb;
        return max(max_cnt * 2 - n, n % 2);
    }
};
