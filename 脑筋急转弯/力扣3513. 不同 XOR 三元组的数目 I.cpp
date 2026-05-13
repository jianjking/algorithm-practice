#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)return 1;
        if (n == 2)return 2;
        int cnt = 1;
        while (n > 0) {
            n >>= 1;
            cnt++;
        }
        return pow(2, cnt);
    }
};