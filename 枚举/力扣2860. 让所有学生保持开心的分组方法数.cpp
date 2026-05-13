#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int countWays(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = nums[0] == 0 ? 0 : 1;
        int cnt = 0;
        for (int i = 0;i < n;i++) {
            cnt++;
            if ((i == n - 1 || cnt < nums[i + 1]) && cnt > nums[i])ans++;
        }
        return ans;
    }
};