#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int jump(char ch, char ar,int j,string &limit) {
        while (j >= 0 && limit[j] != ch)j = next[j];
        return j;
    }
    int dfs(string& s, string&limit,int n, int m, int i, int j, int free, vector<vector<vector<int>>>& dp) {
        if (j == m)return 0;
        if (i == n)return 1;
        if (dp[i][j][free] != -1)return dp[i][j][free];
        int ans = 0;
        char old = s[i];
        if (free) {
            for (char ch = 'a';ch <= 'z';ch++) {
                ans = (ans + dfs(s, limit, n, m, i + 1, jump(ch,limit[j],j,limit) + 1, 1, dp)) % mod;
            }
        }
        else {
            for (char ch = 'a';ch < old;ch++) {
                ans = (ans + dfs(s, limit, n, m, i + 1, jump(ch, limit[j],j,limit) + 1, 1, dp)) % mod;
            }
            ans = (ans + dfs(s, limit, n, m, i + 1, jump(old, limit[j],j,limit) + 1, 0, dp)) % mod;
        }
        dp[i][j][free] = ans;
        return ans;
    }
    vector<int>next;
    int kmp(string& s1, string& s2) {
        int n = s1.size();
        int m = s2.size();
        int x = 0;
        int y = 0;
        while (x < n && y < m) {
            if (s1[x] == s2[y]) {
                x++;
                y++;
            }
            else if (y == 0) {
                x++;
            }
            else {
                y = next[y];
            }
        }
        return y == m ? x - y : -1;
    }
    int findGoodStrings(int n, string s1, string s2, string evil) {
        int m = evil.size();
        vector<vector<vector<int>>>dp(n, vector<vector<int>>(m, vector<int>(2, -1)));
        next.assign(m, -1);
        if (m > 1) {
            next[1] = 0;
            int i = 2;
            int cv = 0;
            while (i < m) {
                if (evil[i - 1] == evil[cv]) {
                    next[i++] = ++cv;
                }
                else if (cv == 0) {
                    next[i++] = 0;
                }
                else{
                    cv = next[cv];
                }
            }
        }
        int ans1 = dfs(s1,evil, n, m, 0, 0, 0,dp);
        dp.assign(n, vector<vector<int>>(m, vector<int>(2, -1)));
        int ans2 = dfs(s2, evil, n, m, 0, 0, 0, dp);
        int ans = (ans2 - ans1 + mod) % mod;
        if (kmp(s1, evil) == -1)ans++;
        return ans;
    }
};