#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
    // 给定间距 score，检查能否在每个区间 [s, s+d] 里各选一个数，
    // 且相邻选择的数至少相差 score。
    static bool check(const vector<int>& start, int d, int score) {
        long long x = LLONG_MIN / 4;            // 避免 x+score 溢出 UB
        for (int s : start) {
            long long L = s, R = (long long)s + d;
            // 当前这段能选的最小值 = 既要 >= 上一个选值+score，又要 >= 左端点 L
            x = max(x + (long long)score, L);
            if (x > R) return false;            // 放不下就失败
        }
        return true;
    }

public:
    int maxPossibleScore(vector<int>& start, int d) {
        sort(start.begin(), start.end());       // 必须按起点升序
        int n = (int)start.size();

        // 上界（开区间）：如果 n 个数间距都 >= S，
        // 总跨度 >= (n-1)*S，必须 ≤ (start.back()+d - start.front())
        // => S ≤ floor((range)/(n-1))。+1 做成二分的右边“开区间”端点。
        int left = 0;
        int right = (start.back() + d - start.front()) / (n - 1) + 1;

        // 二分答案：check(mid) 单调（score 越大越难放下）
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (check(start, d, mid)) left = mid;  // 可行，拉高
            else right = mid;                      // 不可行，压低
        }
        return left;
    }
};
