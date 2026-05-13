#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int f(int status, int i, vector<vector<int>>& dp, vector<int>& cnt, vector<int>& sum) {
        if (status == 0)return 1;
        if (i == cnt.size())return 0;
        if (dp[status][i] != -1)return dp[status][i];
        dp[status][i] = 0;
        for (int j = status;j > 0;j = (j - 1) & status) {
            if (sum[j] <= cnt[i]) {
                dp[status][i] = f(status ^ j, i + 1, dp, cnt, sum);
                if (dp[status][i])break;
            }
        }
        if (!dp[status][i]) {
            dp[status][i] = f(status, i + 1, dp, cnt, sum);
        }
        return dp[status][i];
    }
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        int n = 1;
        for (int i = 1;i < nums.size();i++) {
            if (nums[i - 1] != nums[i])n++;
        }
        vector<int>cnt(n);
        sort(nums.begin(), nums.end());
        int c = 1;
        for (int i = 1, j = 0;i < nums.size();i++) {
            if (nums[i] != nums[i - 1]) {
                cnt[j++] = c;
                c = 1;
            }
            else {
                c++;
            }
        }
        int m = quantity.size();
        cnt[n - 1] = c;
        sort(cnt.begin(), cnt.end(), greater<int>());
        if (cnt.size() > m) cnt.resize(m);

        vector<int>sum(1 << m, 0);
        for (int i = 0;i < m;i++) {
            int a = (1 << i);
            for (int j = 0;j < a;j++) {
                sum[a | j] = sum[j] + quantity[i];
            }
        }
        vector<vector<int>>dp(1 << m, vector<int>(n, -1));
        return f((1 << m) - 1, 0, dp, cnt, sum);
    }
};