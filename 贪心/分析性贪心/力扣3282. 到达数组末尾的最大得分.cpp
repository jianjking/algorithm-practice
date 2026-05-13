#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        int mx = nums[0];
        long long ans = 0;
        int pre = 0;
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] > nums[pre]) {
                ans += 1LL * (i - pre) * nums[pre];
                mx = nums[i];
                pre = i;
            }
        }
        ans += 1LL * (n - 1 - pre) * mx;
        return ans;
    }
};