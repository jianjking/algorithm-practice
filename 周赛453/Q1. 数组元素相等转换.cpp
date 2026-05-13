#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool canMakeEqual(vector<int>& nums, int k) {
        int tmp = k;
        int n = nums.size();
        vector<int>num = nums;
        for (int i = 0;i < n - 1;i++) {
            if (num[i] != 1) {
                tmp--;
                num[i + 1] *= -1;
            }
        }
        if (tmp >= 0 && num[n - 1] == 1)return true;
        num = nums;
        tmp = k;
        for (int i = 0;i < n - 1;i++) {
            if (num[i] != -1) {
                tmp--;
                num[i + 1] *= -1;
            }
        }
        return (tmp >= 0) && (num[n - 1] == -1);
    }
};