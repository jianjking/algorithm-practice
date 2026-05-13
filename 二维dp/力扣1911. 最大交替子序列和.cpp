#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    long long dfs(int i, int j,int n, vector<int>& nums, vector<vector<long long>>& dp) {
        if (i == n)return 0;
        long long& res = dp[i][j];
        if (res != LLONG_MAX / 4)return res;
        int x = j == 0 ? 1 : -1;
        res = max(dfs(i + 1, j, n, nums, dp), x * nums[i] + dfs(i + 1, 1 ^ j, n, nums, dp));
        return res;

    }
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>>dp(n, vector<long long>(2, LLONG_MAX/4));
        return dfs(0, 0,n,nums, dp);
    }
};