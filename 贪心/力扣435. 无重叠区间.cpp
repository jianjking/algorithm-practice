#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//贪心你可以把它当作日常生活中你遇到了会怎么样做
//这道题就是按照结尾排序最划算
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
            });
        int ans = 0;
        int time = INT_MIN;
        int n = intervals.size();
        for (int i = 0;i < n;i++) {
            if (time <= intervals[i][0]) {
                ans++;
                time = intervals[i][1];
            }
        }
        return n - ans;
    }
};