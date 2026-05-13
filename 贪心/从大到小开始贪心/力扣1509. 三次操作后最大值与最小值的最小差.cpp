#include<iostream>
#include<vector>
using namespace std;
//找4个最大值和最小值加枚举
class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if (n <= 4)return 0;
        vector<int>ax(4, INT_MIN);
        vector<int>in(4, INT_MAX);
        for (auto& p : nums) {
            int i = 3;
            while (i >= 0 && p > ax[i]) {
                i--;
            }
            for (int j = 3;j > i + 1;j--) {
                ax[j] = ax[j - 1];
            }
            if (i < 3) {
                ax[i + 1] = p;
            }
            i = 3;
            while (i >= 0 && p < in[i]) {
                i--;
            }
            for (int j = 3;j > i + 1;j--) {
                in[j] = in[j - 1];
            }
            if (i < 3) {
                in[i + 1] = p;
            }
        }
        int ans = INT_MAX;
        for (int i = 0;i <= 3;i++) {
            ans = min(ans, ax[i] - in[3 - i]);
        }
        return ans;
    }
};