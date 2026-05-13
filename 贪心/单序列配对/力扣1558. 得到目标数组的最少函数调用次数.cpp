#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int mx = 0;
        for (int i = 0;i < n;i++) {
            int tmp = nums[i];
            if (tmp)sum++;
            int j = 0;
            while (tmp) {
                tmp >>= 1;
                j++;
                if (tmp) {
                    sum++;
                }
            }
            mx = max(mx, 0);
        }
        return sum;
    }
};