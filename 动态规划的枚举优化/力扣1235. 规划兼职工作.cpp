#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int find1(vector<vector<int>>& num, int target, int r) {
        int l = 0;
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (num[mid][1] <= target) {
                l = mid + 1;
                ans = mid;
            }
            else {
                r = mid - 1;
            }
        }
        return ans;
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>>num(n, vector<int>(3));
        for (int i = 0;i < n;i++) {
            num[i][0] = startTime[i];
            num[i][1] = endTime[i];
            num[i][2] = profit[i];
        }
        sort(num.begin(), num.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
            });
        vector<int>dp(n);
        dp[0] = num[0][2];
        for (int i = 1;i < n;i++) {
            dp[i] = dp[i - 1];
            if (num[i][0] < num[0][1]) {
                dp[i] = max(dp[i], num[i][2]);
            }
            else {
                int m = find1(num, num[i][0], i);
                dp[i] = max(dp[i], dp[m] + num[i][2]);
            }
        }
        return dp[n - 1];
    }
};