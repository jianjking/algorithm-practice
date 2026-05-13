#include <bits/stdc++.h>
using namespace std;

struct compare {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        if (a[0] != b[0]) return a[0] < b[0]; // 价格
        if (a[1] != b[1]) return a[1] < b[1]; // 行
        return a[2] < b[2];                   // 列
    }
};

class Solution {
public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid,
                                            vector<int>& pricing,
                                            vector<int>& start, int k) {
        int n = grid.size(), m = grid[0].size();
        int low = pricing[0], high = pricing[1];
        int si = start[0], sj = start[1];

        vector<vector<int>> ans;
        queue<pair<int,int>> q;
        q.push({si, sj});

        // 起点先判断是否是商品（>1 且在区间内）
        if (grid[si][sj] > 1 && grid[si][sj] >= low && grid[si][sj] <= high) {
            ans.push_back({si, sj});
            if ((int)ans.size() == k) return ans;
        }
        if (grid[si][sj] != 0) grid[si][sj] = 0; // 标记访问

        int d4[5] = {1,0,-1,0,1};

        while (!q.empty() && (int)ans.size() < k) {
            int N = q.size();
            // 按“价格→行→列”收集同一层的所有候选
            set<vector<int>, compare> layer;

            for (int t = 0; t < N; ++t) {
                auto [i, j] = q.front(); q.pop();
                for (int d = 0; d < 4; ++d) {
                    int ni = i + d4[d], nj = j + d4[d+1];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                    if (grid[ni][nj] == 0) continue; // 墙或已访问

                    // 如果是候选商品（>1 且价格在区间），加入该层集合
                    if (grid[ni][nj] > 1 && grid[ni][nj] >= low && grid[ni][nj] <= high) {
                        layer.insert({grid[ni][nj], ni, nj});
                    }

                    q.push({ni, nj});
                    grid[ni][nj] = 0; // 进队即标记，防止重复入队
                }
            }

            // 这一层按排序选入答案
            for (auto it = layer.begin(); it != layer.end() && (int)ans.size() < k; ++it) {
                ans.push_back({(*it)[1], (*it)[2]});
            }
        }
        return ans;
    }
};
