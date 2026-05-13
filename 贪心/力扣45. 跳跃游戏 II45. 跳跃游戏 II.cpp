#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        int cur = 0;
        int n = nums.size();
        int ans = 0;
        int next = 0;
        for (int i = 0;i < n;i++) {
            if (i > cur) {
                ans++;
                cur = next;
            }
            next = max(next, i + nums[i]);
        }
        return ans;
    }
};