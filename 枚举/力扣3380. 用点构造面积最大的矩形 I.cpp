#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxRectangleArea(vector<vector<int>>& points) {
        int n = points.size();
        int ans = -1;
        // 枚举两个点作为矩形的左下角和右上角
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
            // 左下角坐标
            int xa = min(points[i][0], points[j][0]), ya = min(points[i][1], points[j][1]);
            // 右上角坐标
            int xb = max(points[i][0], points[j][0]), yb = max(points[i][1], points[j][1]);

            auto check = [&]() {
                int cnt = 0;
                for (int k = 0; k < n; k++) {
                    // 点在矩形外
                    if (points[k][0] < xa || points[k][0] > xb) continue;
                    if (points[k][1] < ya || points[k][1] > yb) continue;
                    // 是矩形的顶点
                    if ((points[k][0] == xa || points[k][0] == xb) && (points[k][1] == ya || points[k][1] == yb)) { cnt++; continue; }
                    return false;
                }
                return cnt == 4;
                };
            if (check()) ans = max(ans, (xb - xa) * (yb - ya));
        }
        return ans;
    }
};

作者：TsReaper
链接：https ://leetcode.cn/problems/maximum-area-rectangle-with-point-constraints-i/solutions/3013928/mei-ju-by-tsreaper-n259/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。