#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0;
        int r = nums.size()-1;
        int i = 0;
        while (i <= r) {
            if (nums[i] == 0) {
                swap(nums[i], nums[r]);
                l++;
                i++;
            }
            else if (nums[i] == 1) {
                i++;
            }
            else {
                swap(nums[i], nums[r]);
                r--;
            }
        }
    }
};