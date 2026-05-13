#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int>> g(n);
        for (auto& e : paths) {
            int x = e[0] - 1, y = e[1] - 1; // 编号改从 0 开始
            g[x].push_back(y);
            g[y].push_back(x); // 建图
        }

        vector<int> color(n);
        for (int i = 0; i < n; i++) {
            bool used[5]{};
            for (int j : g[i]) {
                used[color[j]] = true;
            }
            while (used[++color[i]]);
        }
        return color;
    }
};

