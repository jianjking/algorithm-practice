#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        int d = nums[n - 1];
        for (int i = n - 2;i >= 0;i--) {
            if (nums[i] > d) {
                int k = (nums[i] + d - 1) / d;
                ans += k - 1;
                d = nums[i] / k;
            }
            else {
                d = nums[i];
            }
        }
        return ans;
    }
};