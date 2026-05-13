#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    void f(vector<int>& need, int m, string& needle) {
        if (m == 1)return;
        need[1] = 0;
        int i = 2;
        int cn = 0;
        while (i < m) {
            if (needle[i - 1] == needle[cn]) {
                need[i++] = ++cn;
            }
            else if (cn > 0) {
                cn = need[cn];
            }
            else {
                need[i++] = 0;
            }
        }


    }
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        vector<int>need(m, -1);
        f(need, m, needle);
        int x = 0;
        int y = 0;
        while (x < n && y < m) {
            if (haystack[x] == needle[y]) {
                x++;
                y++;
            }
            else if (y == 0)x++;
            else {
                y = need[y];
            }
        }
        return y == m ? x - y : -1;
    }
};