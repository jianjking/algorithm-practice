#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        unordered_map<int, int>f;
        f[0] = 1;
        int cnt = 0;
        long long ans = 0;
        for (auto& p : nums) {
            cnt ^= p;
            ans += f[cnt];
            f[cnt]++;
        }
        return ans;
    }
};