#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        vector<int>graph(n, 0);
        int m = queries.size();
        vector<int>ans(m, 0);
        vector<vector<int>>vis(n, vector<int>(2, false));
        int cnt = 0;
        for (int i = 0;i < m;i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            graph[queries[i][0]] = queries[i][1];
            if (a > 0 && graph[a - 1] == graph[a] && (!vis[a][0])) {
                cnt++;
                vis[a][0] = true;
                vis[a - 1][1] = true;
            }
            if (a < n - 1 && graph[a] != graph[a + 1] && (vis[a][1])) {
                cnt--;
                vis[a][1] = false;
                vis[a + 1][0] = false;
            }
            if (a > 0 && graph[a - 1] != graph[a] && (vis[a][0])) {
                cnt--;
                vis[a][0] = false;
                vis[a - 1][1] = false;
            }
            if (a < n - 1 && graph[a] == graph[a + 1] && (!vis[a][1])) {
                cnt++;
                vis[a][1] = true;
                vis[a + 1][0] = true;
            }
        }
        return ans;
    }
};