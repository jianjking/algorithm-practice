#include<iostream>
#include<vector>
#include<set>
using namespace std;
struct Cmp {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        if (a[0] != b[0]) return a[0] < b[0];  // dist 小的排前面
        if (a[1] != b[1]) return a[1] < b[1];  // row 小的排前面
        return a[2] < b[2];                   // col 小的排前面
    }
};

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size(), m = moveTime[0].size();
        // GGG 存 {dist, row, col}
        set<vector<int>, Cmp> GGG;
        GGG.insert({ 0, 0, 0 });

        vector<vector<int>> dis(n, vector<int>(m, INT_MAX));
        dis[0][0] = 0;

        // 四个方向
        int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };
        // 每走一步固定 +1
        const int STEP_COST = 1;

        while (!GGG.empty()) {
            auto tmp = *GGG.begin();
            GGG.erase(GGG.begin());
            int curDist = tmp[0], x = tmp[1], y = tmp[2];

            // 如果这是过时条目，直接跳过
            if (curDist > dis[x][y]) continue;

            // 到终点可以直接返回最优距离
            if (x == n - 1 && y == m - 1) return curDist;

            // 松弛四个邻居
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                int nd = max(moveTime[nx][ny], curDist) + STEP_COST;
                if (nd < dis[nx][ny]) {
                    // 更新距离，插入新条目
                    dis[nx][ny] = nd;
                    GGG.insert({ nd, nx, ny });
                }
            }
        }

        return dis[n - 1][m - 1];  // 如果不可达，就还是 INT_MAX
    }
};