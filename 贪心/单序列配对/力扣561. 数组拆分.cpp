#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return a > b;
            });
        int n = nums.size();
        int ans = 0;
        for (int i = 1;i < n;i+=2) {
            ans += nums[i];
        }
        return ans;
    }
};