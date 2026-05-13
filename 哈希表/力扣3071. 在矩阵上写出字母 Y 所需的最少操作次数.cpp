#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        vector<int>map1(3,0);
        vector<int>map2(3,0);
        int n = grid.size();
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                if ((j != i )||( n - 1 - j != i )|| (i >= n / 2 && j == n / 2))map1[grid[i][j]]++;
                else map2[grid[i][j]]++;
            }
        }
        int ans = INT_MAX;
        for (int i = 0;i < 3;i++) {
            int cnt = map2[i];
            int res = INT_MIN;
            if (i != 0) {
                res = max(res, map1[0]);
            }
            if (i!= 1) {
                res = max(res, map1[1]);
            }
            if (i != 2)res = max(res, map1[2]);
            if (res == INT_MIN)continue;
            ans = min(ans, n * n - res - cnt);
        }
        return ans;
    }
};