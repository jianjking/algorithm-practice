#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minGroupsForValidAssignment(vector<int>& balls) {
        map<int, int>f;
        for (auto& p : balls) {
            f[p]++;
        }
        vector<int>nums;
        for (auto& p : f) {
            nums.push_back(p.second);
        }
        sort(nums.begin(), nums.end());

        int n = nums.size();
        for (int j = nums[0];j >= 1;j--) {
            int ans = 0;
            for (int i = 0;i < n;i++) {
                if (nums[i] / j < nums[i] % j) {
                    ans = 0;
                    break;
                }
                ans += (nums[i] + j) / (j + 1);
            }
            if (ans)return ans;
        }
        return -1;
    }
};