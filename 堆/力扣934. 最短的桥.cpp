#include <bits/stdc++.h>
using namespace std;

struct compare{
    bool operator()(const vector<int>& a, const vector<int>& b) const{
        if (a[2] != b[2]) return a[2] < b[2]; // 先按 dist
        if (a[1] != b[1]) return a[1] < b[1];
        return a[0] < b[0];
    }
};

class Solution {
public:
    vector<int> arr;

    // 注意：这里的 q 要和下面 set 的模板参数一致
    bool dfs(int i, int j, vector<vector<int>>& grid, int n, set<vector<int>, compare>& q){
        if (i < 0 || i >= n || j < 0 || j >= n) return false; // 越界直接 false
        if (grid[i][j] == 0) return true;     // 水：告诉上层“我贴水了”
        if (grid[i][j] == 2) return false;    // 访问过的陆地

        grid[i][j] = 2;                       // 标记陆地已访问
        bool an = false;                      // 是否邻水

        for (int z = 0; z < 4; z++){
            int ni = i + arr[z];
            int nj = j + arr[z + 1];
            if (ni >= 0 && ni < n && nj >= 0 && nj < n){
                if (dfs(ni, nj, grid, n, q)) an = true; // 只对界内邻居递归
            }
        }
        if (an) q.insert({i, j, 0});          // 边界格进队（dist=0）
        return false;                         // 不向上“传染”邻水（设计如此）
    }

    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        set<vector<int>, compare> q;          // 用自定义比较器，按 dist 升序
        arr = {1, 0, -1, 0, 1};

        bool found = false;                   // 找到第一座岛后，双层都停
        for (int i = 0; i < n && !found; i++){
            for (int j = 0; j < n; j++){
                if (grid[i][j] == 1){
                    dfs(i, j, grid, n, q);
                    found = true;
                    break;
                }
            }
        }

        while (!q.empty()){
            auto tmp = *q.begin();
            q.erase(q.begin());
            int i = tmp[0], j = tmp[1], dist = tmp[2];

            for (int z = 0; z < 4; z++){
                int ni = i + arr[z];
                int nj = j + arr[z + 1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < n){
                    if (grid[ni][nj] == 1) return dist;   // 碰到第二岛
                    if (grid[ni][nj] == 0){
                        grid[ni][nj] = 2;                 // 访问标记
                        q.insert({ni, nj, dist + 1});
                    }
                }
            }
        }
        return -1;
    }
};
