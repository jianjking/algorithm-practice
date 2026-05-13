#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 1;i < n;i++) {
            int c = nums[i] - nums[i - 1];
            if (c <= 0) {
                ans += abs(c) + 1;
                nums[i] += abs(c)+1;
            }
        }
        return ans;
    }
};