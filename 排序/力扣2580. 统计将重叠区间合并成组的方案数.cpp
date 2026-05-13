#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        sort(ranges.begin(),ranges.end(), [](auto& a, auto& b) { return a[0] < b[0]; });
        int ans = 1, max_r = -1;
        for (auto& p : ranges) {
            if (p[0] > max_r) { // 无法合并
                ans = ans * 2 % 1'000'000'007; // 新区间
            }
            max_r = max(max_r, p[1]); // 合并
        }
        return ans;
    }
};
