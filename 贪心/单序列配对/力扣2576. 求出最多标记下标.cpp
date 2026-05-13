#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0, j = (n + 1) / 2;j < n && i < n / 2;j++) {
            if (2 * nums[i] <= nums[j]) {
                i++;
                ans++;
            }
        }
        return 2 * ans;
    }
};