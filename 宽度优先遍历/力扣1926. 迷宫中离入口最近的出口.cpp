#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//dfs不行呢，你为什么这么喜欢dfs
class Solution {
public:
    int limitx;
    int limity;
    int dfs(vector<vector<char>>& maze, int i, int j, int step) {
        int n = maze.size();
        int m = maze[0].size();
        if (i < 0 || i >= n || j < 0 || j >= m || maze[i][j] != '.')return INT_MAX;
        if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && (i != limitx || j != limity))return step;
        vector<int>vec = { -1,0,1,0,-1 };
        int ans = INT_MAX;
        for (int z = 0;z < 4;z++) {
            int i1 = i + vec[z];
            int j1 = j + vec[z + 1];
            ans = min(ans, dfs(maze, i1, j1, step + 1));
        }
        return ans;
    }
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        limitx = entrance[0];
        limity = entrance[1];
        int a = dfs(maze, limitx, limity, 0);
        return a == INT_MAX ? -1 : a;
    }
};
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size();
        int m = maze[0].size();
        int limitx = entrance[0];
        int limity = entrance[1];
        queue<vector<int>>f;
        f.push({ limitx,limity,0 });
        vector<int>vec = { -1,0,1,0,-1 };
        maze[limitx][limity] = '+';
        while (!f.empty()) {
            int sz = f.size();
            for (int i = 0;i < sz;i++) {
                vector<int>tmp = f.front();
                int a = tmp[0];
                int b = tmp[1];
                int c = tmp[2];

                f.pop();
                if ((a == 0 || b == 0 || a == n - 1 || b == m - 1) && (a != limitx || b != limity)) {
                    return c;
                }
                for (int i = 0;i < 4;i++) {
                    int a1 = a + vec[i];
                    int b1 = b + vec[i + 1];
                    if (a1 >= 0 && a1 < n && b1 >= 0 && b1 < m && maze[a1][b1] == '.') {
                        f.push({ a1,b1,c + 1 });
                        maze[a1][b1] = '+';
                    }
                }
            }
        }
        return -1;
    }
};