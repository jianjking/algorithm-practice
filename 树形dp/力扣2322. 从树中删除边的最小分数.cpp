#include<iostream>
#include<vector>
using namespace std;
class Solution {
private:
    vector<int>s;
    vector<int>dfn;

    int cnt;
public:
    void f(vector<vector<int>>& graph, vector<int>& nums, vector<int>& sum, int root) {
        int i = cnt++;
        dfn[root] = i;
        sum[i] = nums[root];
        for (auto& p : graph[root]) {
            if (dfn[p] == -1) {
                f(graph, nums, sum, p);
                s[i] += s[dfn[p]];
                sum[i] ^= sum[dfn[p]];


            }
        }
    }
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        cnt = 0;
        int n = nums.size();
        s.assign(n, 1);
        dfn.assign(n, -1);

        vector<vector<int>>graph(n);
        for (auto& p : edges) {
            graph[p[0]].push_back(p[1]);
            graph[p[1]].push_back(p[0]);
        }
        vector<int>sum(n);

        int in = INT_MAX;

        f(graph, nums, sum, 0);
        int m = edges.size();
        for (int i = 0;i < m;i++) {
            for (int j = i + 1;j < m;j++) {
                int a1 = max(dfn[edges[i][0]], dfn[edges[i][1]]);
                int b1 = max(dfn[edges[j][0]], dfn[edges[j][1]]);
                int pre = min(a1, b1);
                int back = max(a1, b1);
                int c1;
                int c2;
                int c3;
                if (back < pre + s[pre]) {
                    c1 = sum[back];
                    c2 = sum[pre] ^ sum[back];
                    c3 = sum[0] ^ sum[pre];
                    int d1 = max(c1, max(c2, c3));
                    int d2 = min(c1, min(c2, c3));
                    in = min(in, d1 - d2);
                }
                else {
                    c1 = sum[back];
                    c2 = sum[pre];
                    c3 = sum[0] ^ sum[pre] ^ sum[back];
                    int d1 = max(c1, max(c2, c3));
                    int d2 = min(c1, min(c2, c3));
                    in = min(in, d1 - d2);
                }
            }
        }
        return in;
    }
};