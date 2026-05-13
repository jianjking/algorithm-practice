#include<iostream>
#include<vector>
using namespace std;
//最优解动态规划枚举左下角

class Solution {
public:
    //不是最优解就是枚举
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>>grid(n, vector<int>(m, 0));
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (!matrix[i][j]) {
                    grid[i][j] = 0;
                }
                else if (i == 0)grid[i][j] = matrix[i][j];
                else {
                    grid[i][j] = grid[i - 1][j] + 1;
                }
            }
        }
        int ans = 0;
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (grid[i][j]) {
                    int mn = grid[i][j];
                    ans++;
                    for (int z = 1;j + z < m && z < grid[i][j];z++) {
                        mn = min(mn, grid[i][j + z]);
                        if (mn >= z + 1)ans++;
                        else {
                            break;
                        }
                    }
                }
            }
        }
        return ans;
    }
};
//最优解动态规划
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>>arr(n, vector<int>(m));
        int ans = 0;
        for (int i = 0;i < m;i++) {
            arr[0][i] = matrix[0][i];
            ans += arr[0][i];
        }
        for (int i = 1;i < n;i++) {
            arr[i][0] = matrix[i][0];
            ans += arr[i][0];
        }
        for (int i = 1;i < n;i++) {
            for (int j = 1;j < m;j++) {
                if (matrix[i][j])
                    arr[i][j] = min(min(arr[i - 1][j], arr[i - 1][j - 1]), arr[i][j - 1]) + 1;
                else arr[i][j] = 0;
                ans += arr[i][j];
            }
        }
        return ans;
    }
};