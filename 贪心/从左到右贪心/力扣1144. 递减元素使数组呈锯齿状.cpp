#include<iostream>
#include<vector>
using namespace std;
//分情况讨论
class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();
        vector<int>num(n + 2,INT_MAX);
        for (int i = 1;i <= n;i++) {
            num[i] = nums[i - 1];
        }
        int ans1 = 0;
        int ans2 = 0;
        for (int i = 1;i <= n;i++) {
            if (i % 2) {
                int c = min(num[i - 1], num[i + 1]);
                if(num[i]>=c)
                ans1 += num[i]-min(num[i - 1], num[i + 1]) + 1; 
            }

            else {
                int c = min(num[i - 1], num[i + 1]);
                if (num[i] >= c)
                    ans2 += num[i] - min(num[i - 1], num[i + 1]) + 1;
            } 
        }
        return min(ans1, ans2);
    }
};