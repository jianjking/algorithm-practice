#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int cnt = 0;
        int ans = 0;
        int n = nums.size();
        for (int l = 0, r = 0;r < n;r++) {
            if (nums[r] == 0)cnt++;
            while (cnt > k) {
                if (nums[l] == 0)cnt--;
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};