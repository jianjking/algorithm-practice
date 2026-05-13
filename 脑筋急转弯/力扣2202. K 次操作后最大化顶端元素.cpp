#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maximumTop(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1 && k % 2 == 1)return-1;

        int ans = INT_MIN;

        for (int i = 0;i < min(k - 1, n);i++) {
            ans = max(ans, nums[i]);
        }
        if (k < n)ans = max(ans, nums[k]);
        return ans;
    }
};