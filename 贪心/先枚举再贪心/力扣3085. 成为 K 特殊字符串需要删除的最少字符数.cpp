#include<iostream>
#include<Vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int>arr(26, 0);
        vector<int>nums;
        for (auto& p : word) {
            arr[p - 'a']++;
        }
        long long sum = 0;

        for (auto& p : arr) {
            if (p) {
                nums.push_back(p);
                sum += p;
            }
        }
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = INT_MAX;
        for (int i = 0;i < n;i++) {
            auto p = upper_bound(nums.begin(), nums.end(), nums[i] + k) - nums.begin();
            long long sum1 = 0;
            for (int j = i;j < p;j++) {
                sum1 += nums[j];
            }
            ans = min(ans, (int)(sum - sum1) - (int)(n - p) * (nums[i] + k));
        }
        return ans;
    }
};