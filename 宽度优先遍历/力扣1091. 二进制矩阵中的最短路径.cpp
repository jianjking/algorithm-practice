#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int arr[8][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1} };
        queue<vector<int>>f;
        if (grid[0][0])return -1;
        f.push({ 0,0,1 });
        int n = grid.size();
        while (!f.empty()) {
            int sz = f.size();
            for (int j = 0;j < sz;j++) {
                vector<int>tmp = f.front();
                f.pop();
                int a = tmp[0];
                int b = tmp[1];
                int step = tmp[2];
                if (a == n - 1 && b == n - 1)return step;
                for (int i = 0;i < 8;i++) {
                    int a1 = a + arr[i][0];
                    int b1 = b + arr[i][1];
                    if (a1 >= 0 && b1 >= 0 && a1 < n && b1 < n && grid[a1][b1] != 1) {
                        f.push({ a1,b1,step + 1 });
                        grid[a1][b1] = 1;

                    }
                }
            }
        }
        return -1;
    }
};