#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1; // 二进制全为 1
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            if (i != x) {
                ans &= x;
            }
        }
        return max(ans, 0);
    }
};
