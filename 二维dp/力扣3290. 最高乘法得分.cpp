#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;
class Solution {
public:
    ll dfs(int i, int j, int n, vector<vector<ll>>& dp, vector<int>& a, vector<int>& b) {
        if (j > 3)return 0;
        if (i >= n)return LLONG_MIN / 2;
        if (dp[i][j] != LLONG_MIN / 2)return dp[i][j];
        ll ans = dfs(i + 1, j, n, dp, a, b);
        ans = max(ans, (ll)a[j] * b[i] + dfs(i + 1, j + 1, n, dp, a, b));
        dp[i][j] = ans;
        return ans;
    }
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<vector<ll>>dp(n, vector<ll>(4, LLONG_MIN / 2));
        return dfs(0, 0, n, dp, a, b);
    }
};