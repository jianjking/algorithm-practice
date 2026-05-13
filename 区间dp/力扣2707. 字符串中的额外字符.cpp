#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    unordered_set<string>map;
    int mn;
    int dfs(int l, int r, vector<vector<int>>& dp, string& s) {
        if (l > r)return 0;
        if (map.count(s.substr(l, r - l + 1)) == 1)return 0;
        if (r - l + 1 <= mn)return r - l + 1;
        if (dp[l][r] != -1)return dp[l][r];
        int& res = dp[l][r];
        res = INT_MAX;
        for (int i = l;i < r;i++) {
            res = min(res, dfs(l, i, dp, s) + dfs(i + 1, r, dp, s));
        }
        return res;
    }
    int minExtraChar(string s, vector<string>& dictionary) {
        mn = INT_MAX;
        for (auto& p : dictionary) {
            map.insert(p);
            mn = min(mn, (int)p.size());
        }
        int n = s.size();
        vector<vector<int>>dp(n, vector<int>(n, -1));
        dfs(0, n - 1, dp, s);
    }
};