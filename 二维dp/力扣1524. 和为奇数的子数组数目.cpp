#include<iostream>
#include<vector>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>>nums(n, vector<int>(2, 0));
        if (arr[0] % 2)nums[0][1] = 1;
        else nums[0][0] = 1;
        long long sum = nums[0][1];
        for (int i = 1;i < n;i++) {
            if (arr[i] % 2)
            {
                nums[i][0] = nums[i - 1][1];
                nums[i][1] = nums[i - 1][0] + 1;
            }
            else {
                nums[i][0] = nums[i - 1][0] + 1;
                nums[i][1] = nums[i - 1][1];
            }
            sum = (sum + nums[i][1]) % mod;
        }
        return sum;
    }
};