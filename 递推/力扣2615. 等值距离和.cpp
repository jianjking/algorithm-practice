#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long>ans(n, 0);
        unordered_map<int, vector<int>>cnt;
        for (int i = 0; i < n; i++) {
            cnt[nums[i]].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            auto p = lower_bound(cnt[nums[i]].begin(), cnt[nums[i]].end(), i) - cnt[nums[i]].begin();
            if (p == 0) {
                for (auto& p : cnt[nums[i]]) {
                    ans[i] += p - i;
                }
            }
            else {
                int m = cnt[nums[i]].size();
                ans[i] = ans[cnt[nums[i]][p - 1]] + (p - (m - p)) * (cnt[nums[i]][p] - cnt[nums[i]][p - 1]);
            }
        }
        return ans;
    }
};