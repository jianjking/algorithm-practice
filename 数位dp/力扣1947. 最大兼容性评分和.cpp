#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int i, int status, int n, int m, vector<vector<int>>& sudents, vector<vector<int>>& mentors, vector<vector<int>>& dp) {
        if (i == m)return 0;
        if (dp[i][status] != -1)return dp[i][status];
        int ans = INT_MIN;
        for (int j = 0;j < m;j++) {
            if (((status >> j) & 1) == 0) {
                int tmp = 0;
                for (int z = 0;z < n;z++) {
                    if (sudents[i][z] == mentors[j][z]) {
                        tmp++;
                    }
                }
                ans = max(ans, tmp + dfs(i + 1, status | (1 << j), n, m, sudents, mentors, dp));
            }
        }
        dp[i][status] = ans;
        return ans;
    }
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int m = students.size();
        int n = students[0].size();
        vector<vector<int>>dp(m, vector<int>(1 << m, -1));
        return dfs(0, 0, n, m, students, mentors, dp);
    }
};