#include<iostream>
#include<vector>
#include<set>
using namespace std;
class Solution {
public:
    int partitionString(string s) {
        int ans = 1;
        set<int>graph;
        int n = s.size();
        for (int i = 0;i < n;i++) {
            if (graph.find(s[i]) == graph.end()) {
                graph.insert(s[i]);
            }
            else {
                ans++;
                graph.clear();
                graph.insert(s[i]);
            }
        }
        return ans;
    }
};