#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long dfs(int i, int n, int j, vector<vector<long long>>& dp, int x, vector<int>& nums) {
        if (i == n)return 0;
        long long& res = dp[i][j];
        if (res != -1)return res;
        if (nums[i] % 2 == j) {
            res = nums[i] + dfs(i + 1, n, j, dp, x, nums);
            return res;
        }
        res = max(dfs(i + 1, n, j, dp, x, nums), nums[i] - x + dfs(i + 1, n, j ^ 1, dp, x, nums));
        return res;
    }
    long long maxScore(vector<int>& nums, int x) {
        int n = nums.size();
        vector < vector<long long >> dp(n, vector<long long>(2, -1));
        return dfs(0, n, nums[0] % 2, dp, x, nums);
    }
};