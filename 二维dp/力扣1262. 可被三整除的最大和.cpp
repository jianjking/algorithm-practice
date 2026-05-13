#include<iostream>
#include<vector>
using namespace std;
int dfs(int cur, int n, vector<vector<int>>& dp, vector<int>& nums, int sum) {
    if (cur == n) {
        return sum == 0 ? 0 : INT_MIN / 2;
    }
    int& ans = dp[cur][sum];
    int take = nums[cur] + dfs(cur + 1, n, dp, nums, (sum - nums[cur] % 3 + 3) % 3);
    int skip = dfs(cur + 1, n, dp, nums, sum);
    ans = max(take, skip);

    return ans;
}
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>dp(n, vector<int>(3, -1));
        return dfs(0, n, dp, nums, 0);
    }
};