#include<iostream>
#include<vector>
#include<map>;
using namespace std;
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        map<int, int>f;
        f.insert({ 0,1 });
        int ans = 0;
        int cnt = 0;
        for (auto& p : nums) {
            if (p % 2)
                cnt++;
            ans += f[cnt - k];
            f[cnt]++;
        }
        return ans;
    }
};