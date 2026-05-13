#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
class compare {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        if (a[0] != b[0]) return a[0] < b[0];  // 处理时间小的优先
        return a[1] < b[1];                    // 索引小的优先
    }
};

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        for (int i = 0; i < n; i++) tasks[i].push_back(i); // 记录原始索引

        sort(tasks.begin(), tasks.end()); // 按到达时间排序

        set<vector<int>, compare> cnt;
        vector<int> ans;
        long long time = 0;
        int ptr = 0; // 指针，表示处理到第几个任务

        while (ptr < n || !cnt.empty()) {
            // 把所有到达时间 <= 当前 time 的任务丢进优先队列
            while (ptr < n && tasks[ptr][0] <= time) {
                cnt.insert({ tasks[ptr][1], tasks[ptr][2] });
                ptr++;
            }

            if (!cnt.empty()) {
                auto cur = *cnt.begin();
                cnt.erase(cnt.begin());
                ans.push_back(cur[1]); // 存索引
                time += cur[0];        // 更新 CPU 时间
            }
            else {
                // CPU 空闲 -> 跳到下一个任务的到达时间
                time = tasks[ptr][0];
            }
        }

        return ans;
    }
};
