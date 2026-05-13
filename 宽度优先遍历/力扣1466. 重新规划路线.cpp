#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>>graph(n);
        int ans = 0;
        for (int i = 0;i < n - 1;i++) {
            graph[connections[i][0]].push_back(i);
            graph[connections[i][1]].push_back(i);
        }
        queue<int>f;
        vector<bool>p1(n - 1, false);
        f.push(0);
        while (!f.empty()) {
            int tmp = f.front();
            f.pop();
            for (auto& p : graph[tmp]) {
                if (p1[p])continue;
                p1[p] = true;
                int a = connections[p][1];
                int b = connections[p][0];

                ans += a == tmp ? 0 : 1;
                f.push(a == tmp ? b : a);
            }
        }
        return ans;
    }
};