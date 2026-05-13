#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        int g = numsDivide[0];
        int n = numsDivide.size();
        for (int i = 1;i < n;i++) {
            g = gcd(g, numsDivide[i]);
        }
        sort(nums.begin(), nums.end());
        int i = 0;
        for (;i < nums.size();i++) {
            if (g % nums[i] == 0)break;
        }
       return i == n ? -1 : i;
    }
};