#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // row[x] = {所有在该x列上的障碍y}
        unordered_map<int, set<int>> row;
        // col[y] = {所有在该y行上的障碍x}
        unordered_map<int, set<int>> col;
        for (auto& p : obstacles) {
            row[p[0]].insert(p[1]);
            col[p[1]].insert(p[0]);
        }

        int x = 0, y = 0;
        int dirc = 0; // 0=N,1=E,2=S,3=W
        int mx = 0;
        int dxy[5] = {0, 1, 0, -1, 0}; // (dx,dy) = (dxy[dir], dxy[dir+1])

        for (int p : commands) {
            if (p == -1) {            // 右转
                dirc = (dirc + 1) & 3;
            } else if (p == -2) {     // 左转
                dirc = (dirc + 3) & 3;
            } else if (p > 0) {       // 前进 p 步（一次性跳到可能的最远位置）
                int x1 = x + p * dxy[dirc];
                int y1 = y + p * dxy[dirc + 1];

                if (x1 == x) { // 纵向移动（改y）
                    auto itset = row.find(x);
                    if (itset != row.end()) {
                        auto& S = itset->second;
                        if (y1 > y) { // 向上 N
                            auto it = S.lower_bound(y + 1);
                            if (it != S.end() && *it <= y1) {
                                y1 = *it - 1;
                            }
                        } else {      // 向下 S
                            auto it = S.lower_bound(y);
                            if (it != S.begin()) {
                                --it; // <= y-1 的最大障碍
                                if (*it >= y1) {
                                    y1 = *it + 1;
                                }
                            }
                        }
                    }
                } else { // 横向移动（改x）
                    auto itset = col.find(y);
                    if (itset != col.end()) {
                        auto& S = itset->second;
                        if (x1 > x) { // 向右 E
                            auto it = S.lower_bound(x + 1);
                            if (it != S.end() && *it <= x1) {
                                x1 = *it - 1;
                            }
                        } else {      // 向左 W
                            auto it = S.lower_bound(x);
                            if (it != S.begin()) {
                                --it; // <= x-1 的最大障碍
                                if (*it >= x1) {
                                    x1 = *it + 1;
                                }
                            }
                        }
                    }
                }

                x = x1; y = y1;
                mx = max(mx, x * x + y * y);
            }
            // 其余情况(p==0) 不动
        }
        return mx;
    }
};
