#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int n = grid[0].size();
        long long ans = numeric_limits<long long>::max();
        long long topRemain = 0;
        for (int v : grid[0])
            topRemain += v;
        long long bottomCollected = 0;
        // 枚举第一个机器人在第 j 列下楼
        for (int j = 0; j < n; ++j) {
            topRemain -= grid[0][j];
            // 第二个机器人只能拿到上下剩余部分的最大值
            ans = min(ans, max(topRemain, bottomCollected));
            bottomCollected += grid[1][j];
        }
        return ans;
    }
};
