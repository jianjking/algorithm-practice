#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long f(int i, vector<vector<int>>& questions, vector<long long>& dp) {
        int n = questions.size();
        if (i == n)return 0;
        if (dp[i] != -1)return dp[i];
        long long ans = f(i + 1, questions, dp);
        long long cur = questions[i][0];
        if (i + questions[i][1] + 1 <= n) {
            cur += f(i + questions[i][1] + 1, questions, dp);
        }
        ans = max(cur, ans);
        dp[i] = ans;
        return ans;
    }
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long>dp(n, -1);
        return f(0, questions, dp);
    }
};