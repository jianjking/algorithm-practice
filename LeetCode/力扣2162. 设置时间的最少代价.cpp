#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        // 给定输入的最小花费
        auto cost = [&](int m, int s) -> int {
            if (m < 0 || m > 99 || s < 0 || s > 99) {
                // 输入不合法
                return INT_MAX;
            }
            vector<int> digits = {m / 10, m % 10, s / 10, s % 10};
            // 寻找起始位
            int start = 0;
            while (start < 4 && digits[start] == 0) {
                ++start;
            }
            
            int res = 0;   // 最小花费
            int prev = startAt;
            for (int i = start; i < 4; ++i) {
                int d = digits[i];
                if (d != prev) {
                    // 此时需要先移动再输入
                    prev = d;
                    res += moveCost;
                }
                res += pushCost;
            }
            return res;
        };
        
        int mm = targetSeconds / 60, ss = targetSeconds % 60;
        return min(cost(mm, ss), cost(mm - 1, ss + 60));   // 两种可能方案的较小值
    }
};

