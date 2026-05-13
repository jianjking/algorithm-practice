#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    string rankTeams(vector<string>& votes) {
        int n = votes[0].size();
        vector<vector<int>>dp(26, vector<int>(n, 0));
        int m = votes.size();
        for (int i = 0;i < m;i++) {
            for (int j = 0;j < n;j++) {
                dp[votes[i][j] - 'A'][j]--;
            }
        }
        string ans = votes[0];
        sort(ans.begin(), ans.end(), [&](char a, char b) {
            if (dp[a - 'A'] != dp[b - 'A'])
                return dp[a - 'A'] < dp[b - 'A'];
            return a < b;
            });
        return ans;

    }
};