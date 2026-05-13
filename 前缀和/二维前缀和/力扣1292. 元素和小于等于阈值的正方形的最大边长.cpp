#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>>sum(n + 1, vector<int>(m + 1, 0));
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
        int ans = 0;
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                int l = i;
                int r = j;
                while (l <= n && r <= m) {
                    int tmp = sum[l][r] - sum[l][j - 1] - sum[i - 1][r] + sum[i - 1][j - 1];
                    if (tmp <= threshold)ans = max(ans, l - i + 1);
                    else break;
                    l++;
                    r++;
                }
            }
        }
        return ans;
    }
};