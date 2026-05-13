#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        long long  sum = 0;
        long long ans = 0;
        if (k == 0)return nums1 == nums2 ? 0 : -1;
        for (int i = 0;i < n;i++) {
            int c = nums1[i] - nums2[i];
            sum += c;
            if (abs(c) % k != 0)return -1;
            ans += abs(c) / k;
        }
        if (sum != 0)return -1;
        return ans / 2;
    }
};