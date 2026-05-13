#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        int n = grid.size();
        vector<int>num;
        for (int i = 0;i < n;i++) {
            sort(grid[i].begin(), grid[i].end(), [](int a, int b) {
                return a > b;
                });
            for (int j = 0;j < limits[i];j++) {
                num.push_back(grid[i][j]);
            }
        }
        sort(num.begin(), num.end(), [](int a, int b) {
            return a > b;
            });
        long long ans = 0;
        for (int i = 0;i < k;i++) {
            ans += num[i];
        }
        return ans;
    }
};