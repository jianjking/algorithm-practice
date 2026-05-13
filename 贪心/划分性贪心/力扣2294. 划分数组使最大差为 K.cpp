#include<iostream>
#include<Vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 1;
        int mn = nums[0];
        int mx = nums[0];
        int n = nums.size();
        for (int i = 1;i < n;i++) {
            mn = min(mn, nums[i]);
            mx = max(mx, nums[i]);
            if (mx - mn > k) {
                mn = nums[i];
                mx = nums[i];
                ans++;
            }
        }
        return ans;
    }
};