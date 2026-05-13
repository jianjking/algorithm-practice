#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = INT_MIN;
        int l = 0;
        int r = n - 1;
        while (l <= r) {
            ans = max(ans, nums[r] + nums[l]);
            r--;
            l++;
        }
        return ans;
    }
};