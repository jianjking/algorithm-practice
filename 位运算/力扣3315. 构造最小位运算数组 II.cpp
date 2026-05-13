#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int>ans(n, 0);
        for (int i = 0;i < n;i++) {
            bool an = true;
            int tmp = nums[i];
            while (tmp > 0) {
                if ((tmp & 1) == 0) {
                    an = false;
                    break;
                }
                tmp >>= 1;
            }
            if (an) {
                tmp = 1;
                while (tmp < nums[i])tmp *= 2;
                ans[i] = nums[i] - tmp / 2;
            }
            else {
                if ((nums[i] & 1) == 1) {
                    int j;
                    for (j = 0;j < 32;j++)if (((nums[i] >> j) & 1) == 0)break;
                    ans[i] = nums[i] - pow(2, j - 1);
                }
                else ans[i] = -1;
            }
        }
        return ans;
    }
};