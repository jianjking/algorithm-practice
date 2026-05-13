#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long largestPerimeter(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long ans = -1;
        long long sum = 0;
        for (auto& p : nums) {
            sum += p;
      }
        for (int i = n - 1;i >= 2;i--) {
            int x = nums[i];
            if (sum - x > x) {
                return sum;
            }
            sum -= x;
        }
        return -1;
    }
};