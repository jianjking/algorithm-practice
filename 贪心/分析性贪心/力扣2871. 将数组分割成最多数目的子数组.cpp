#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxSubarrays(vector<int>& nums) {
        int ans = 0;
        int a = -1; // -1 就是 111...1，和任何数 AND 都等于那个数
        for (int x : nums) {
            a &= x;
            if (a == 0) {
                ans++; // 分割
                a = -1;
            }
        }
        return max(ans, 1); // 如果 ans=0 说明所有数的 and>0，答案为 1
    }
};