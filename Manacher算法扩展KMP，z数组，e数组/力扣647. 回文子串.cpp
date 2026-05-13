#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int countSubstrings(string s) {
        string tmp = "#";
        for (int i = 0;i < s.size();i++) {
            tmp += s[i];
            tmp += "#";
        }
        int n = tmp.size();
        vector<int>p(n, 0);
        for (int i = 0, c = 0, r = 0;i < n;i++) {
            int len = r > i ? min(r - i, p[2 * c - i]) : 1;
            while (i + len < n && i - len >= 0 && tmp[i - len] == tmp[i + len])len++;
            if (i + len > r) {
                c = i;
                r = i + len;
            }
            p[i] = len;
        }
        int ans = 0;
        for (auto p1 : p) {
            ans += p1 / 2;
        }
        return ans;
    }
};