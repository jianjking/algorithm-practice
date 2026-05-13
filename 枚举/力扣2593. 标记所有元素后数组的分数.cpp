#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;
class Solution {
public:
    long long findScore(vector<int>& nums) {
        int n = nums.size();
        vector<int>tmp(n);
        iota(tmp.begin(), tmp.end(), 0);
        stable_sort(tmp.begin(), tmp.end(), [&](auto a, auto b) {
            return nums[a] < nums[b];
            });
        long long ans = 0;
        vector<bool>vis(n, false);
        for (int i = 0;i < n;i++) {
            if (vis[tmp[i]])continue;
            ans += nums[i];
            vis[i] = true;
            if (i > 0)vis[i - 1] = true;
            if (i < n - 1)vis[i + 1] = true;
        }
        return ans;
    }
};