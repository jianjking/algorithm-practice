#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>>vis(n, vector<int>(m, false));
        vis[0][0] = true; 
        deque<vector<int>>f;
        int arr[] = {-1,0,1,0,-1};
        f.push_back({ 0,0,grid[0][0] });
        while (!f.empty()) {
            vector<int>tmp = f.front();
            f.pop_front();
            int a = tmp[0];
            int b = tmp[1];
            int c = tmp[2];
            if (a == n - 1 && b == m - 1)return true;
            for (int i = 0;i < 4;i++) {
                int a1 = a + arr[i];
                int b1 = b + arr[i + 1];
                if (a1 < 0 || a1 >= n || b1 < 0 || b1 >= m||vis[a1][b1])continue;
                int c1 = grid[a1][b1];
                if (i == 0) {
                    if ((c == 2 || c == 5 || c == 6) && (c1 == 2 || c1 == 3 || c1 == 4)) {
                        vis[a1][b1] = true;
                        f.push_back({ a1,b1,c1 });
                    }
                }
                else if (i == 1) {
                    if ((c == 1 || c == 4 || c == 6) && (c1 == 1 || c1 == 3 || c1 == 5)) {
                        vis[a1][b1] = true;
                        f.push_back({ a1,b1,c1 });
                    }
                }
                else if (i == 2) {
                    if ((c == 2 || c == 3 || c == 4) && (c1 == 2 || c1 == 5 || c1 == 6)) {
                        vis[a1][b1] = true;
                        f.push_back({ a1,b1,c1 });
                    }
                }
                else {
                    if ((c1 == 1 || c1 == 4 || c1 == 6) && (c == 1 || c == 3 || c == 5)) {
                        vis[a1][b1] = true;
                        f.push_back({ a1,b1,c1 });
                    }
                }
            }
        }
        return false;
    }
};