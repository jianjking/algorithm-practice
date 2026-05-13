#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int i, int j,int n, vector<vector<int>>& dp, vector<int>& obstacles) {
        if (i == n-1)return 0;
        if (obstacles[i] == j)return INT_MIN/2;
        int& res = dp[i][j];
        if (res != -1)return res;
        if (obstacles[i + 1] == j) {
            res = 1 + min(dfs(i + 1, (j + 1) % 3, n, dp, obstacles), dfs(i + 1, (j + 2) % 3, n, dp, obstacles));
        }
        else res = dfs(i + 1, j, n, dp, obstacles);
        return res;
    }
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<vector<int>>dp(n, vector<int>(3, -1));
        return dfs(0, 2,n, dp, obstacles);
    }
};