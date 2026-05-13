#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals) {
        int arr[26];
        for (int i = 0;i < 26;i++) {
            arr[i] = i + 1;
        }
        for (int i = 0;i < chars.size();i++) {
            arr[chars[i] - 'a'] = vals[i];
        }
        int n = s.size();
        vector<int>dp(n + 1, 0);
        int ans = INT_MIN;
        for (int i = 1;i <= n;i++) {
            dp[i] = max(arr[s[i - 1] - 'a'], dp[i - 1] + arr[s[i - 1] - 'a']);
            ans = max(dp[i], ans);
        }
        return max(ans, 0);
    }
};