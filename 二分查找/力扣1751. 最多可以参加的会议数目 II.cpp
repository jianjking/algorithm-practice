#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int find(int l, int r, vector<vector<int>>& events, int target) {
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (events[mid][1] < target) {
            ans = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return ans;
}
class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        sort(events.begin(), events.end(), [](auto a, auto b) {
            return a[1] < b[1];
            });
        vector<vector<int>>dp(n, vector<int>(k + 1.0));
        for (int i = 1;i <= k;i++) {
            dp[0][i] = events[0][2];
        }
        for (int i = 1;i < n;i++) {
            int pre = find(0, i, events, events[i][0]);
            for (int j = 1;j <= k;j++) {
                
                dp[i][j] = max(dp[i - 1][j], (pre == -1 ? 0 : dp[pre][j - 1]) + events[i][2]);
            }
        }
        return dp[n - 1][k];
    }
};