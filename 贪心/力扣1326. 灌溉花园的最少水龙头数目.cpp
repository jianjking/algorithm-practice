#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int>right(n + 1);
        for (int i = 0;i <= n;i++) {
            int r = max(0, i - ranges[i]);
            int l = min(n, i + ranges[i]);
            right[r] = max(right[r], l);
        }
        int cur = 0;
        int next = 0;
        int ans = 0;
        for (int i = 0;i < n;i++) {
            next = max(next, right[i]);
            if (i == cur) {
                if (next > i) {
                    cur = next;
                    ans++;
                }
                else {
                    return -1;
                }
            }
        }
        return ans;
    }
};