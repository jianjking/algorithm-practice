#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int n = grid.size();
        int m = grid[0].size();
        int limit = grid[0][0] % x;
        vector<int>nums;
        nums.reserve(n * m);
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (grid[i][j] % x != limit)return -1;
                nums.push_back(grid[i][j]);
            }
        }
        sort(nums.begin(), nums.end());
        n = nums.size();
        int ans = 0;
        int a = nums[n / 2];
        for (auto& p : nums) {
            ans += (abs(p - a)) / x;
        }
        return ans;
    }
};