#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        map<int, int>p;
        long long ans = 0;
        int n = nums.size();
        for (int i = 0;i < n;i++) {
            ans += p[nums[i] - i];
            p[nums[i] - i]++;
        }
        return (long long)n * (n - 1) / 2 - ans;
    }
};