#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int get(int ss, int bit) {
        return (ss / bit) % 3;
    }
    int set(int ss, int v, int bit) {
        int pre = get(ss, bit);
        return ss + (v - pre) * bit;
    }
    int dfs(int i, int j, int ss, int nei, int wai, int n, int m, vector<vector<vector<vector<vector<int>>>>>& dp, int bit) {
        if (i == n)return 0;
        if (j == m)return dfs(i + 1, 0, ss, nei, wai, n, m, dp, 1);
        if (dp[i][j][ss][nei][wai] != -1)return dp[i][j][ss][nei][wai];
        int l = j == 0 ? 0 : get(ss, bit / 3);
        int up = get(ss, bit);
        int num = 0;
        if (l > 0)num += 1;
        if (up > 0)num += 1;
        int pre = l == 0 ? 0 : (l == 1 ? -30 : 20);
        pre += up == 0 ? 0 : (up == 1 ? -30 : 20);
        int ans = dfs(i, j + 1, set(ss, 0, bit), nei, wai, n, m, dp, 3 * bit);
        if (nei > 0)ans = max(ans, pre + 120 - 30 * num + dfs(i, j + 1, set(ss, 1, bit), nei - 1, wai, n, m, dp, bit * 3));
        if (wai > 0)ans = max(ans, pre + 40 + 20 * num + dfs(i, j + 1, set(ss, 2, bit), nei, wai - 1, n, m, dp, 3 * bit));
        dp[i][j][ss][nei][wai] = ans;
        return ans;
    }
    int getMaxGridHappiness(int m, int n, int a, int b) {
        if (m > n)swap(m, n);
        int s = 1;
        for (int i = 0;i < m;i++, s *= 3) {}
        vector<vector<vector<vector<vector<int>>>>>dp(n, vector<vector<vector<vector<int>>>>(m, vector<vector<vector<int>>>(s, vector<vector<int>>(a + 1, vector<int>(b + 1, -1)))));
        return dfs(0, 0, 0, a, b, n, m, dp, 1);
    }
};