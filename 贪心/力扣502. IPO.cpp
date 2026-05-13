#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<vector<int>>cur(n, vector<int>(2));
        for (int i = 0;i < n;i++) {
            cur[i][0] = profits[i];
            cur[i][1] = capital[i];
        }
        priority_queue<int>heap;
        sort(cur.begin(), cur.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
            });
        for (int i = 0, j = 0;k > 0;) {
            while (i < n && w >= cur[i][1]) {
                heap.push(cur[i][0]);
                i++;
            }
            if (heap.empty()) {
                break;
            }
            w += heap.top();
            heap.pop();
            k--;
        }
        return w;
    }
};
