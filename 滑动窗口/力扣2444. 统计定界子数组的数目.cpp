#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int premin = -1;
        int premax = -1;
        int boundary = -1;
        int n = nums.size();
        long long ans = 0;
        for (int i = 0;i < n;i++) {
            if (nums[i] == minK) {
                premin = i;
            }
            if (nums[i] == maxK) {
                premax = i;
            }
            if (nums[i]<minK || nums[i]>maxK) {
                boundary = i;
            }
                ans += max(0, min(premin, premax) - boundary);
        }
        return ans;
    }
};