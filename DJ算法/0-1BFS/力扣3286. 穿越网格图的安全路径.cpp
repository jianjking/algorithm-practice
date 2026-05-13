#include<iostream>
#include<deque>
#include<vector>
using namespace std;
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>>dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = grid[0][0];
        int arr[] = { -1,0,1,0,-1 };
        deque<pair<int, int>>q;
        q.push_front({ 0,0 });
        while (!q.empty()) {
            int i = q.front().first;
            int j = q.front().second;
            q.pop_front();
            for (int z = 1;z <= 4;z++) {
                int a = i + arr[z - 1];
                int b = j + arr[z];
                if (a >= 0 && a < n && b >= 0 && b < m && dist[a][b]>dist[i][j] + grid[a][b]) {
                    dist[a][b] = dist[i][j] + grid[a][b];
                    if (grid[a][b] == 1)q.push_back({ a,b });
                    else q.push_front({ a,b });
                }
            }
        }
        return  dist[n - 1][m - 1] < health;
    }
};