#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void dfs(int i, int j,int m,int n, vector<vector<int>>& vis, int idx, int idy) {
        if (i < 0 || j < 0 || i >= m || j >= n || vis[i][j] == 0)return;
        vis[i][j] = 1;
        dfs(i + idx, j + idy, m, n, vis, idx, idy);
    }
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>>vis(m, vector<int>(n, -1));
        for (auto& p : guards) {
            vis[p[0]][p[1]] = 0;
        }
        for (auto& p : walls) {
            vis[p[0]][p[1]] = 0;
        }
        for (auto& p : guards) {
            dfs(p[0] + 1, p[1], m,n,vis, 1, 0);
            dfs(p[0], p[1] - 1, m,n,vis, 0, -1);
            dfs(p[0] - 1, p[1], m,n,vis, -1, 0);
            dfs(p[0], p[1] +1, m,n,vis, 0, 1);
        }
        int ans = 0;
        for (int i = 0;i < m;i++) {
            for (int j = 0;j < n;j++) {
                if (vis[i][j] == -1)ans++;
            }
        }
        return ans;
    }
};