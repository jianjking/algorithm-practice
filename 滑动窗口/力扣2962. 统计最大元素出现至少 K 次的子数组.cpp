#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = INT_MIN;
        for (int i = 0;i < n;i++) {
            ans = max(ans, nums[i]);
        }
        long long cnt = 0;
        int count = 0;
        for (int l = 0, r = 0;r < n;r++) {
            if (nums[r] == ans)count++;

            while (count == k) {
                if (nums[l] == ans)count--;
                l++;
            }
            cnt += l;
        }
        return cnt;
    }
};