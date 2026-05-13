#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = isWater.size(), m = isWater[0].size();
        vector<vector<int>> ans(n, vector<int>(m, -1));
        queue<pair<int, int>> q;
        int d[5] = { -1,0,1,0,-1 };

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (isWater[i][j]) { ans[i][j] = 0; q.push({ i,j }); }

        while (!q.empty()) {
            auto a = q.front();
            int x = a.first;
            int y = a.second;
            q.pop();
            for (int k = 0; k < 4; ++k) {
                int nx = x + d[k], ny = y + d[k + 1];
                if (0 <= nx && nx < n && 0 <= ny && ny < m && ans[nx][ny] == -1) {
                    ans[nx][ny] = ans[x][y] + 1;
                    q.push({ nx, ny });
                }
            }
        }
        return ans;
    }
};
