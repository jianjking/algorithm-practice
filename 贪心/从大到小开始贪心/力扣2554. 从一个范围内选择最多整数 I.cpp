#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        vector<bool>panduan(n + 1, true);
        for (auto& p : banned) {
            if (p <= n)
                panduan[p] = false;
        }
        int sum = 0;
        int ans = 0;
        for (int i = 1;i <= n && sum < maxSum;i++) {
            if (panduan[i]) {
                sum += i;
                ans++;
            }
        }
        if (sum > maxSum)ans--;
        return max(ans, 0);
    }
};