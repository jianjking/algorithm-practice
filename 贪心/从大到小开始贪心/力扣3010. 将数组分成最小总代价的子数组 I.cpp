#include<iostream>
#include<vector>
using namespace std;
//第一个元素必选 然后在后面选最小值和次小值
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int ans = nums[0];
        int prepre = INT_MAX;
        int pre = INT_MAX;
        for (int i = 1;i < nums.size();i++) {
            if (nums[i] < prepre) {
                pre = prepre;
                prepre = nums[i];
            }
            else if (nums[i] < pre) {
                pre = nums[i];
            }
        }
        return ans + prepre + pre;
    }
};