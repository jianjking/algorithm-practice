#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0;i < n;i++) {
            int tmp = nums[i];
            int sum = 0;
            while (tmp) {
                sum += tmp % 10;
                tmp /= 10;
            }
            if (sum == i)return i;
        }
        return -1;
    }
};