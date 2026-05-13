#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)return -1;
        vector<long long>sum(n + 1, 0);
        vector<pair<bool, bool>>pre(n, { false,false });
        pre[0] = { true,true };
        sum[1] = nums[0];
        for (int i = 1; i < n; i++)
        {
            sum[i + 1] = sum[i] + nums[i];
            pre[i] = pre[i - 1];
            if (nums[i] > nums[i - 1]) {
                pre[i].second = false;
            }
            else if (nums[i] < nums[i - 1]) {
                pre[i].first = false;
            }
            else {
                pre[i] = { false,false };
            }
        }
        vector<pair<bool, bool>>back(n, { false,false });
        back[n - 1] = { true,true };
        for (int i = n - 2; i >= 0; i--) {
            back[i] = back[i + 1];
            if (nums[i] < nums[i + 1]) {
                back[i].second = false;
            }
            else if (nums[i] > nums[i + 1]) {
                back[i].first = false;
            }
            else {
                back[i] = { false,false };
            }
        }
        long long ans = LLONG_MAX;
        for (int i = 0; i < n - 1; i++) {
            if (pre[i].first && back[i + 1].second) {
                ans = min(ans, abs(2 * sum[i + 1] - sum[n]));
            }


        }
        return ans == LLONG_MAX ? -1 : ans;
    }
}; ©leetcode