#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int root(int i, vector<int>& father) {
        return i == father[i] ? i : father[i] = root(father[i], father);
    }
    void merge(int i, int j, vector<int>& father, vector<int>& sz, vector<int>& b) {
        int a = root(i, father);
        int c = root(j, father);
        if (a == c) {
            b[a]++;
            return;
        }
        else {
            if (sz[a] <= sz[c]) {
                father[a] = c;
                sz[c] += sz[a];
                b[c] += b[a] + 1;
            }
            else {
                father[c] = a;
                sz[a] += sz[c];
                b[a] += b[c] + 1;
            }
        }
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int>sz(n, 1);
        vector<int>father(n, 1);
        vector<int>b(n, 0);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }
        for (auto p : edges) {
            int a = p[0];
            int c = p[1];
            merge(a, c, father, sz, b);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (father[i] == i) {
                if (sz[i] == 1 || sz[i] == 0)ans++;
                else if ((sz[i] * (sz[i] - 1)) / 2 == b[i])ans++;
            }
        }
        return ans;

    }
};
