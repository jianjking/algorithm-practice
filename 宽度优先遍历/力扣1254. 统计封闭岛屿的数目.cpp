#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int arr[] = { -1,0,1,0,-1 };
        int m = grid[0].size();
        queue<vector<int>>f;
        for (int i = 0;i < n;i++) {
            if (grid[i][0] == 0) {
                grid[i][0] = 1;
                f.push({ i,0 });
                while (!f.empty()) {
                    int sz = f.size();
                    for (int z = 0;z < sz;z++) {
                        int a = f.front()[0];
                        int b = f.front()[1];
                        f.pop();
                        for (int j = 0;j < 4;j++) {
                            int a1 = a + arr[j];
                            int b1 = b + arr[j + 1];
                            if (a1 >= 0 && b1 >= 0 && a1 < n && b1 < m && grid[a1][b1] == 0) {
                                grid[a1][b1] = 1;
                                f.push({ a1,b1 });
                            }
                        }
                    }

                }
            }
        }
        for (int i = 0;i < n;i++) {
            if (grid[i][m - 1] == 0) {
                grid[i][m - 1] = 1;
                f.push({ i,m - 1 });
                while (!f.empty()) {
                    int sz = f.size();
                    for (int z = 0;z < sz;z++) {
                        int a = f.front()[0];
                        int b = f.front()[1];
                        f.pop();
                        for (int j = 0;j < 4;j++) {
                            int a1 = a + arr[j];
                            int b1 = b + arr[j + 1];
                            if (a1 >= 0 && b1 >= 0 && a1 < n && b1 < m && grid[a1][b1] == 0) {
                                grid[a1][b1] = 1;
                                f.push({ a1,b1 });
                            }
                        }
                    }

                }
            }
        }
        for (int i = 0;i < m;i++) {
            if (grid[0][i] == 0) {
                grid[0][i] = 1;
                f.push({ 0,i });
                while (!f.empty()) {
                    int sz = f.size();
                    for (int z = 0;z < sz;z++) {
                        int a = f.front()[0];
                        int b = f.front()[1];
                        f.pop();
                        for (int j = 0;j < 4;j++) {
                            int a1 = a + arr[j];
                            int b1 = b + arr[j + 1];
                            if (a1 >= 0 && b1 >= 0 && a1 < n && b1 < m && grid[a1][b1] == 0) {
                                grid[a1][b1] = 1;
                                f.push({ a1,b1 });
                            }
                        }
                    }

                }
            }
        }
        for (int i = 0;i < m;i++) {
            if (grid[n - 1][i] == 0) {
                grid[n - 1][i] = 1;
                f.push({ n - 1,i });
                while (!f.empty()) {
                    int sz = f.size();
                    for (int z = 0;z < sz;z++) {
                        int a = f.front()[0];
                        int b = f.front()[1];
                        f.pop();
                        for (int j = 0;j < 4;j++) {
                            int a1 = a + arr[j];
                            int b1 = b + arr[j + 1];
                            if (a1 >= 0 && b1 >= 0 && a1 < n && b1 < m && grid[a1][b1] == 0) {
                                grid[a1][b1] = 1;
                                f.push({ a1,b1 });
                            }
                        }
                    }

                }
            }
        }
        int ans = 0;
        for (int i = 1;i < n;i++) {
            for (int j = 1;j < m;j++) {
                if (grid[i][j] == 0) {
                    ans++;
                    grid[i][j] = 1;
                    f.push({ i,0 });
                    while (!f.empty()) {
                        int sz = f.size();
                        for (int z = 0;z < sz;z++) {
                            int a = f.front()[0];
                            int b = f.front()[1];
                            f.pop();
                            for (int j = 0;j < 4;j++) {
                                int a1 = a + arr[j];
                                int b1 = b + arr[j + 1];
                                if (a1 >= 0 && b1 >= 0 && a1 < n && b1 < m && grid[a1][b1] == 0) {
                                    grid[a1][b1] = 1;
                                    f.push({ a1,b1 });
                                }
                            }
                        }

                    }
                }
            }
        }
        return ans;
    }
};