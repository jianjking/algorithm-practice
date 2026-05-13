#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int dfs(int n, int name, vector<vector<int>>& dp) {
        if (n == 0) return 0;                // 当前玩家无子可拿 -> 必败(0)
        int& res = dp[n][name];
        if (res != -1) return res;

        res = 0; // 先假设当前玩家必败，只要找到一招能让对手必败，就改成必胜
        for (int i = 1; i * i <= n; ++i) {
            if (dfs(n - i * i, name ^ 1, dp) == 0) { // 对手必败 -> 我方必赢
                res = 1;
                break;
            }
        }
        return res;
    }

    bool winnerSquareGame(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        return dfs(n, 0, dp); // 先手从 name=0 开始
    }
};
