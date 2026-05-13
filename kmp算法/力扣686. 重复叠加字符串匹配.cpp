#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int n = a.size();
        int m = b.size();
        string tmp = a;
        for (int i = 0;i < (m + n - 1) / n + 1;i++)a += tmp;
        vector<int>next(m);
        next[0] = -1;
        if (b.size() > 1) {
            next[1] = 0;
            int cn = 0;
            for (int i = 2;i < m;) {
                if (b[i - 1] == b[cn]) {
                    next[i++] = ++cn;

                }
                else if (cn == 0) {
                    next[i++] = 0;
                }
                else {
                    cn = next[cn];
                }
            }
        }
        int x = 0;
        int y = 0;
        while (x < a.size() && y < m) {
            if (a[x] == b[y]) {
                x++;
                y++;
            }
            else if (y == 0) {
                x++;
            }
            else {
                y = next[y];
            }
        }
        if (y != m)return -1;
        return (x + n - 1) / n;
    }
};
