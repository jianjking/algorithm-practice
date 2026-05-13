#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        long long sum = 0;
        for (auto& p : nums) {
            sum += p;
        }
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return a > b;
            });
        vector<int>ans;
        int n = nums.size();
        long long s = 0;
        for (int i = 0;i < n && s <= sum / 2;i++) {
            s += nums[i];
            ans.push_back(nums[i]);
        }
        return ans;
    }
};