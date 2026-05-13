#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        int m = rowCosts.size(), n = colCosts.size();
        int x1 = startPos[0], y1 = startPos[1], x2 = homePos[0], y2 = homePos[1];
        if (x1 == x2 && y1 == y2)return 0;
        int left = min(y1, y2), right = max(y1, y2), up = min(x1, x2), down = max(x1, x2);
        int res = 0;
        for (int i = y1 - 1; i >= left; --i)res += colCosts[i];
        for (int i = y1 + 1; i <= right;++i)res += colCosts[i];
        for (int i = x1 - 1; i >= up;--i)res += rowCosts[i];
        for (int i = x1 + 1; i <= down;++i)res += rowCosts[i];
        return res;
    }
};
