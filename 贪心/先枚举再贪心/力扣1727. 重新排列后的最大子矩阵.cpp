#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>>g(n, vector<int>(m, 0));
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (matrix[i][j] == 0) {
                    g[i][j] = 0;
                }
                else if (i == 0) {
                    g[i][j] = 1;
                }
                else {
                    g[i][j] = g[i - 1][j] + 1;
                }
            }
        }
        int ans = INT_MIN;
        for (int i = 0;i < n;i++) {
            vector<int>tmp(m);
            for (int j = 0;j < m;j++) {
                tmp[j] = g[i][j];
            }
            sort(tmp.begin(), tmp.end());
            for (int j = 0;j < m;j++) {
                ans = max(ans, (m - j) * tmp[j]);
            }
        }
        return ans;
    }
};