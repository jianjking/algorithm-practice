#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int minMoves(vector<string>& matrix) {
        queue<vector<int>>f;
        vector<vector<pair<int,int>>>graph(26);
        int n = matrix.size();
        int m = matrix[0].size();
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                if (matrix[i][j] >= 'A' && matrix[i][j] <= 'Z') {
                    int ch = matrix[i][j] - 'A';
                    graph[ch].push_back({ i,j });
                }
            }
        }
        vector<int>arr = { -1,0,1,0,-1 };
        f.push({ 0,0,0,0 });
        while (!f.empty()) {
            int sz = f.size();
            for (int i = 0;i < sz;i++) {
                vector<int>tmp = f.front();
                int a = tmp[0];
                int b = tmp[1];
                int c = tmp[2];
                int d = tmp[3];
                if (a == n - 1 && b == m - 1)return c;
                f.pop();
                for (int j = 0;j < 4;j++) {
                    int a1 = a + arr[j];
                    int b1 = b + arr[j + 1];
                    if (a1 >= 0 && a1 < n && b1 >= 0 && b1 < m && matrix[a1][b1] != '#') {
                        f.push({ a1,b1,c + 1,d });
                        if (matrix[a1][b1] >= 'A' && matrix[a1][b1] <= 'Z' && (d >> (matrix[a1][b1] - 'A')) & 1 == 0) {
                            for (auto& p : graph[matrix[a1][b1] - 'A']) {
                                int a2 = p.first;
                                int b2 = p.second;
                                if (matrix[a2][b2] != '#' && a2 != a1 && b2 != b1) {
                                    f.push({ a2,b2,c + 1,d ^ (1 << (matrix[a1][b1] - 'A')) });
                                    matrix[a2][b2] = '#';
                                }
                            }
                        }
                            matrix[a1][b1] = '#';
                    }
                }
            }
           
        }
        return -1;
    }
};