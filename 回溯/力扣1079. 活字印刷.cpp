#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    unordered_set<string>f;
    void dfs(int i, int n,string& cur,vector<bool>&vis, string& tiles) {
        if (i==n) {
            if (cur == "")return;
            f.insert(cur);
            return;
        }
        dfs(i + 1, n, cur, vis,tiles);
        for (int j = 0;j < n;j++) {
            if (vis[j])continue;
            vis[j] = true;
            cur += tiles[j];
            dfs(i + 1, n, cur, vis, tiles);
            vis[j] = false;
            cur.pop_back();

        }
    }
    int numTilePossibilities(string tiles) {
        int n = tiles.size();
        string s;
        vector<bool>vis(n, false);
        dfs(0, n, s,vis,tiles);
        return f.size();
    }
};