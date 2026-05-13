#include<iostream>
#include<vector>
using namespace std;
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses,
        vector<vector<int>>& prerequisites,
        vector<vector<int>>& queries)
    {
        // 1. 建有向图：u -> v 表示 u 是 v 的先修
        vector<vector<int>> g(numCourses);
        for (auto& e : prerequisites) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
        }

        // 2. 预处理可达关系：reach[i][j] 表示 i 是否能到达 j
        vector<vector<bool>> reach(numCourses, vector<bool>(numCourses, false));
        for (int i = 0; i < numCourses; ++i) {
            queue<int> q;
            q.push(i);
            // 从 i 出发做 BFS
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : g[u]) {
                    if (!reach[i][v]) {
                        reach[i][v] = true;
                        q.push(v);
                    }
                }
            }
        }

        // 3. 回答每个查询
        vector<bool> ans;
        ans.reserve(queries.size());
        for (auto& qv : queries) {
            int u = qv[0], v = qv[1];
            ans.push_back(reach[u][v]);
        }
        return ans;
    }
};
