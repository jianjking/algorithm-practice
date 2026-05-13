#include<iostream>
#include<vector>
using namespace std;
struct GGG {
    int h;
    int m;
    GGG(int h1 = 1, int m1 = 1):h(h1),m(m1) {
        
    }
};
GGG f(vector<vector<int>>& graph, int root, string& s) {
    if (graph[root].empty())return { 1,1 };
    GGG c;
    int m = INT_MIN;
    int max1=INT_MIN;
    int max2 = INT_MIN;
    for (auto& p : graph[root]) {
        GGG a = f(graph, p, s);
        m = max(m, a.m);
        if (a.h > max1&&s[p]!=s[root]) {
            max2 = max1;
            max1 = a.h;
        }
        else if (a.h > max2&&s[p]!=s[root]) {
            max2 = a.h;
        }
    }
    if (max2 != INT_MIN && max1 != INT_MIN) {
        m = max(m, max1 + max2 + 1);

    }
    if (max1 != INT_MIN) { 
        m = max(m, max1 + 1);
        c.h = max1 + 1; }
    c.m = m;
    return c;
}
class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        int root;
        int n = parent.size();
        vector<vector<int>>graph(n);
        for (int i = 0;i < n;i++) {
            int a = parent[i];
            if (a == -1)root = i;
            else {
                graph[a].push_back(i);
            }
        }
        GGG ans = f(graph, root,s);
        return ans.m;
    }
};