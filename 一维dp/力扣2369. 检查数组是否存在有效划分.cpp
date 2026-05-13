#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int i, int n, vector<int>& dp, vector<int>& nums) {
        if (i == n)return 1;
        if (i == n - 1)return 0;
        int& res = dp[i];
        if (res != -1)return res;
        res = 0;
        if (nums[i] == nums[i + 1]) {
            res = max(res, dfs(i + 2, n, dp, nums));
        }
        if (i + 2 < n && nums[i] == nums[i + 1] && nums[i + 2] == nums[i + 1]) {
            res = max(res, dfs(i + 3, n, dp, nums));
        }
        if (i + 2 < n && nums[i] == nums[i + 1] - 1 && nums[i + 2] == nums[i + 1] + 1) {
            res = max(res, dfs(i + 3, n, dp, nums));
        }
        return res;
    }
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n, -1);
        return dfs(0, n, dp, nums);
    }
};