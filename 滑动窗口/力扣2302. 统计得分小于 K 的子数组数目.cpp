#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        long long ans = 0, sum = 0;
        for (int l = 0, r = 0; l < n; l++) {
            while (r < n && (sum + nums[r]) * (r - l + 1) < k) {
                sum += nums[r++];
            }
            ans += r - l;        // r 正好停在第一个不合法处
            sum -= nums[l];
        }
        return ans;
    }
};
