#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = weights.size();
        vector<long long>nums;
        nums.reserve(n);
        for (int i = 0;i < n - 1;i++) {
            nums.push_back(weights[i] + weights[i + 1]);
        }
        long long ans = 0;
        sort(nums.begin(), nums.end());
        int m = nums.size();
        for (int i = 0;i < k - 1;i++) {
            ans += nums[m - 1 - i] - nums[i];
        }
        return ans;
    }
};