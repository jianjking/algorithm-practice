#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
struct compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
            });
        priority_queue<int, vector<int>, compare>heap;
        int n = events.size();
        int min = events[0][0];
        int m = INT_MIN;
        int ans = 0;
        for (int i = 0;i < n;i++) {
            m = max(m, events[i][1]);
        }
        for (int i = min, j = 0;i <= m;i++) {
            while (j < n && i == events[j][0]) {
                heap.push(events[j++][1]);
            }
            while (!heap.empty() && i > heap.top()) {
                heap.pop();
            }
            if (!heap.empty() && i <= heap.top()) {
                ans++;
                heap.pop();
            }

        }
        return ans;
    }
};