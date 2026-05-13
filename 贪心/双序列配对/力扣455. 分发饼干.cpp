#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int n = g.size();
        int m = s.size();
        int ans = 0;
        for (int l1 = 0, l2 = 0;l1 < n && l2 < m;) {
            if (g[l1] <= s[l2]) {
                l1++;
                l2++;
                ans++;
            }
            else {
                l2++;
            }
        }
        return ans;
    }
};