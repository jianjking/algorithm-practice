#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
//贪心策略 1 截止日期小的肯定先解决
//2 如果一个课程的代价太大以至于在她后面的课程无法进入我们果断选择代价小的课程
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();
        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
            });
        priority_queue<int>heap;
        int time = 0;
        for (int i = 0;i < n;i++) {
            if (time + courses[i][0] <= courses[i][1]) {
                heap.push(courses[i][0]);
                time += courses[i][0];
            }
            else {
                if (!heap.empty() && courses[i][0] < heap.top()) {
                    time += courses[i][0] - heap.top();
                    heap.pop();
                    heap.push(courses[i][0]);
                }
            }
        }
        return heap.size();
    }
};