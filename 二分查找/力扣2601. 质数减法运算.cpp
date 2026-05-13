#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        vector<int>vis(1001, false);
        vector<int>num;
        num.resize(1000);
        for (int i = 2; i < 1001; i++) {
            if (vis[i])continue;
            num.push_back(i);
            for (int j = i; j <= 1000; j += i) {
                vis[j] = true;
            }
        }
        int n = nums.size();
        auto place = lower_bound(num.begin(), num.end(), nums[0]) - num.begin() - 1;
        if (place != -1)nums[0] -= num[place];
        for (int i = 1; i < n; i++) {
            if (nums[i] <= nums[i - 1])return false;
            auto p = lower_bound(num.begin(), num.end(), nums[i] - nums[i - 1]) - num.begin() - 1;
            if (p != -1)nums[i] -= num[p];
        }
        return true;
    }
};