#include<iostream>
#include<vector>
using namespace std;
#include <vector>
#include <unordered_set>
#include <climits>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // 用一个哈希集合存储所有点，编码方式为 x*40001 + y
        unordered_set<int> pointSet;
        pointSet.reserve(points.size() * 2);
        for (auto& p : points) {
            pointSet.insert(p[0] * 40001 + p[1]);
        }

        int ans = INT_MAX;
        int n = points.size();
        // 枚举两点作为矩形的对角
        for (int i = 0; i < n; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j) {
                int x2 = points[j][0], y2 = points[j][1];
                // 要构成矩形对角，x 坐标和 y 坐标都要不同
                if (x1 != x2 && y1 != y2) {
                    // 检查另外两个角 (x1,y2) 和 (x2,y1) 是否存在
                    if (pointSet.count(x1 * 40001 + y2) &&
                        pointSet.count(x2 * 40001 + y1)) {
                        int area = abs(x2 - x1) * abs(y2 - y1);
                        ans = min(ans, area);
                    }
                }
            }
        }

        return ans == INT_MAX ? 0 : ans;
    }
};
