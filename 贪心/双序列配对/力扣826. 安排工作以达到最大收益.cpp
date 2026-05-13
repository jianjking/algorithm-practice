#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int m = worker.size();
        sort(worker.begin(), worker.end());
        priority_queue<int>heap;
        int n = difficulty.size();
        vector<vector<int>>arr(n, vector<int>(2));
        for (int i = 0;i < n;i++) {
            arr[i][0] = difficulty[i];
            arr[i][1] = profit[i];
        }
        sort(arr.begin(), arr.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
            });
        int ans = 0;
        int left = 0;
        for (int i = 0;i < m;i++) {
            while (left < n && worker[i] >= arr[left][0]) {
                heap.push(arr[left][1]);
                left++;
            }
            if (!heap.empty())ans += heap.top();
        }

        return ans;
    }
};