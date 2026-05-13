#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int find1(int l, int r, int target,vector<int>&nums) {
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] >= target) {
                r = mid - 1;
                ans = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return ans;
    }
    int find2(int l, int r, int target, vector<int>& nums) {
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target) {
                l = mid + 1;
                ans = mid;
            }
            else {
                r = mid - 1;
            }
        }
        return ans;
    }
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        long long ans = 0;
        for (int i = 0;i < n;i++) {
            int l = find1(0, i-1, lower - nums[i], nums);
            int r = find2(0, i-1, upper - nums[i], nums);
            if (l == -1 || r == -1)continue;
            ans += r - l + 1;
        }
        return ans;
    }
};