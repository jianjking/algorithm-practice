#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>dp;
vector<vector<int>>graph;
class Solution {
public:
    int shun(char a, int target) {
        int ans = -1;
        int r = graph[a - 'a'].size() - 1;
        int l = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (graph[a - 'a'][mid] > target) {
                ans = graph[a - 'a'][mid];
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return ans == -1 ? graph[a - 'a'][0] : ans;
    }
    int ni(char a, int target) {
        int ans = -1;
        int r = graph[a - 'a'].size() - 1;
        int l = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (graph[a - 'a'][mid] < target) {
                ans = graph[a - 'a'][mid];
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        return ans == -1 ? graph[a - 'a'][graph[a - 'a'].size() - 1] : ans;
    }
    int f(int i, int m, string& ring, string& key) {
        if (i == key.size())return 0;
        if (dp[i][m] != -1)return dp[i][m];
        dp[i][m] = 0;
        if (ring[m] == key[i])dp[i][m] = 1 + f(i + 1, m, ring, key);
        else {
            int a = shun(key[i], m);
            int a1 = (a + ring.size() - m) % ring.size();
            int b = ni(key[i], m);
            int b1 = (m + ring.size() - b) % ring.size();
            dp[i][m] = 1 + min(a1 + f(i + 1, a, ring, key), b1 + f(i + 1, b, ring, key));
        }
        return dp[i][m];
    }
    int findRotateSteps(string ring, string key) {
        dp.clear();
        graph.clear();
        int n = ring.size();
        int m = key.size();
        dp.resize(m, vector<int>(n, -1));
        graph.resize(26);
        for (int i = 0;i < n;i++) {
            graph[ring[i] - 'a'].push_back(i);
        }
        return f(0, 0, ring, key);
    }
};