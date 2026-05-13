#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int cnt = 0;
        vector<vector<int>>ans;ans.reserve(rows * cols);
        int arr[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
        int step = 1;
        int shun = 0;
        while (cnt < rows * cols) {


            for (int p = 0;p < 2;p++) {
                for (int i = 0;i < step;i++) {
                    if (rStart < rows && rStart >= 0 && cStart < cols && cStart >= 0) {
                        ans.push_back({ rStart,cStart });
                        cnt++;
                    }
                    rStart += arr[shun][0];
                    cStart += arr[shun][1];

                }
                shun = (shun + 1) % 4;
            }
            step++;
        }
        return ans;
    }
};