#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int l = 0;
        int  r = 2;
        int n = nums.size();
        int ans = 0;
        while (r < n) {
            if (2 * (nums[l] + nums[r]) == nums[r - 1]) {
                ans++;
            }
            l++;
            r++;
        }
        return ans;
    }
};