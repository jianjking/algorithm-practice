#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int minimumMoves(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0;i < n;i++) {
            if (s[i] == 'X') {
                ans++;
                if (i + 1 < n)s[i + 1] = '0';
                if (i + 2 < n)s[i + 2] = '0';
            }
        }
        return ans;
    }
};