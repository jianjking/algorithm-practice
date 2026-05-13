#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0;k > 0;i++) {
            if (i < n && nums[i] < 0) {
                nums[i] = -nums[i];
                k--;
            }
            else {
                sort(nums.begin(), nums.end());
                if (k % 2)nums[0] = -nums[0];
                break;
            }
        }
        int sum = 0;
        for (auto& p : nums) {
            sum += p;
        }
        return sum;
    }
};