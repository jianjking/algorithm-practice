#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        long long sum = 0;
        int n = grid.size();
        int m = grid[0].size();
        unordered_set<long long>f;
        vector<long long>l(n);
        vector<long long>r(m);
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                sum += grid[i][j];
            }
            f.insert(sum);
        }
        if (sum % 2)return false;
        if (f.find(sum / 2)!=f.end())return true;
        f.clear();
        sum = 0;
        for (int j = 0;j < m;j++) {
          
            for (int i = 0;i < n;i++) {
                sum += grid[i][j];
            }
            f.insert(sum);
        }
        if (f.find(sum / 2) == f.end())return false;
        return true;
    }
};