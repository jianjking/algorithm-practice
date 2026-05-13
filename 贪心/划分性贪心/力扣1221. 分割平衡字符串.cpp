#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int balancedStringSplit(string s) {
        int n = s.size();
        int l = 0;
        int r = 0;
        int ans = 0;
        for (int i = 0;i < n;i++) {
            if (s[i] == 'R')r++;
            else l++;
            if (l == r) {
                ans++;
                l = 0;
                r = 0;
            }
        }
        return ans;
    }
};
