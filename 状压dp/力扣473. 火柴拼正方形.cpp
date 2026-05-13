#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int f(vector<int>& dp, int state, int limit, int cur, int rest, vector<int>& nums) {
        if (rest == 0)return state == 0;
        if (dp[state] != -1)return dp[state];
        int n = nums.size();
        dp[state] = 0;
        for (int i = 0;i < n;i++) {
            if ((state & (1 << i)) != 0 && cur + nums[i] <= limit) {

                if (cur + nums[i] == limit) {
                    dp[state] = f(dp, state ^ (1 << i), limit, cur + nums[i] - limit, rest - 1, nums);
                    if (dp[state])break;
                }
                else {
                    dp[state] = f(dp, state ^ (1 << i), limit, cur + nums[i], rest, nums);
                    if (dp[state])break;
                }
            }
        }
        return dp[state];
    }
    bool makesquare(vector<int>& matchsticks) {
        int sum = 0;
        int n = matchsticks.size();
        for (int i = 0;i < n;i++) {
            sum += matchsticks[i];
        }
        if (sum % 4 != 0)return false;
        int limit = sum / 4;
        int state = (1 << n) - 1;
        vector<int>dp((1 << n), -1);
        return f(dp, state, limit, 0, 4, matchsticks);
    }
};