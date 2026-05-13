#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long>sum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = nums[i] + sum[i];
        }
        unordered_map<int, int>cnt;
        long long ans = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            if (cnt.count(nums[i])) {
                if (sum[cnt[nums[i]]] > sum[i]) {
                    cnt[nums[i]] = i;
                }
            }
            else {
                cnt[nums[i]] = i;
            }
            if (cnt.count(nums[i] + k)) {
                ans = max(ans, sum[i + 1] - sum[cnt[nums[i] + k]]);
            }
            if (cnt.count(nums[i] - k)) {
                ans = max(ans, sum[i + 1] - sum[cnt[nums[i] - k]]);
            }


        }
        return ans == LLONG_MIN ? 0 : ans;
    }
};