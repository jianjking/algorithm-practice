#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int arr[3] = { 1,0,1 };
    int dfs(int i, int j,int n,int m, int times, vector<vector<vector<int>>>& dp, vector<vector<int>>& coins) {
        if (i == n - 1 && j == m - 1)return times == 0 ? coins[i][j] : max(0, coins[i][j]);
        int& res = dp[i][j][times];
        if (res != INT_MIN / 2)return res;
        for (int x = 0; x <2; x++) {
            int a = i + arr[x];
            int b = j + arr[x + 1];
            if (a >= 0 && a < n && b >= 0 && b < m) {
                res = max(res,coins[i][j] +dfs(a, b, n, m, times, dp, coins));
                if (times > 0)res = max(res, dfs(a, b, n, m, times - 1, dp, coins));
            }
        }
        return res;
    }
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size();
        int m = coins[0].size();
        vector<vector<vector<int>>>dp(n, vector<vector<int>>(m, vector<int>(2, INT_MIN / 2)));
        return dfs(0, 0,n,m,2,dp, coins);
    }
};
