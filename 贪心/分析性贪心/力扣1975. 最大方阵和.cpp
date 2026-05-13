#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int cnt = 0;
        long long sum1 = 0;
        long long sum2 = 0;
        int mn1 = INT_MAX;
        int mx1 = INT_MIN;
        int n = matrix.size();
        int m = matrix[0].size();
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (matrix[i][j] >= 0) {
                    mn1 = min(mn1, matrix[i][j]);
                    sum1 += matrix[i][j];
                }
                else {
                    mx1 = max(mx1, matrix[i][j]);
                    cnt++;
                    sum2 += matrix[i][j];
                }
            }
        }
        if (cnt % 2 == 0)return sum1 + abs(sum2);
        if (abs(mx1) > mn1)return sum1 + abs(sum2) - 2 * mn1;
        return sum1 + abs(sum2) + 2 * mx1;
    }
};