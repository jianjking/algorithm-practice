#include<iostream>
#include<vector>'
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        nums[0] = nums[0] - k;
        int n = nums.size();
        int ans = 1;
        for (int i = 1;i < n;i++) {
            int tmp = nums[i];
            nums[i] = max(nums[i - 1] + 1, nums[i] - k);
            if (nums[i] <= tmp + k) {
                ans++;
            }
            else {
                nums[i] = tmp + k;
            }
        }
        return ans;
    }
};
