#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int countNicePairs(vector<int>& nums) {
        unordered_map<int, int>cnt;
        int n = nums.size();
        int ans = 0;
        for (int i = 0;i < n;i++) {
            int tmp = nums[i];
            int num = 0;
            while (tmp > 0) {
                num += 10 * num + tmp % 10;
                tmp /= 10;
            }
            num -= nums[i];
            ans = (ans + cnt[num]) % mod;
            cnt[num]++;
        }
        return ans;
    }
};