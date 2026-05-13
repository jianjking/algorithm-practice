#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int>cnt;
        int sum = 0;
        int ans = 0;
        cnt[0]++;
        for (int i = 0;i < n;i++) {
            sum += nums[i];
            int  tmp = (sum + (long long)k * 10000000) % k;
            ans += cnt[tmp];
            cnt[tmp]++;
        }
        return ans;
    }
};