#include<iostream>
#include<vector>
using namespace std;
class Solution {
    vector<vector<int>> G;
    int n, m;
    bool vis[20][20];               // 假设最大 20×20，按需调整
    const int di[4] = { -1, 0, 1, 0 };
    const int dj[4] = { 0, 1, 0,-1 };

    int dfs(int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= m) return 0;
        if (G[i][j] == 0 || vis[i][j]) return 0;

        int tmp = G[i][j];
        vis[i][j] = true;

        int best = 0;
        for (int k = 0; k < 4; ++k) {
            best = max(best, dfs(i + di[k], j + dj[k]));
        }

        vis[i][j] = false;
        return tmp + best;
    }

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        G = grid;
        n = G.size();
        m = G[0].size();
        memset(vis, 0, sizeof(vis));

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (G[i][j] > 0) {
                    ans = max(ans, dfs(i, j));
                }
            }
        }
        return ans;
    }
};
