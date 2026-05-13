#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int removePalindromeSub(string s) {
        int n = s.size();
        int l = 0;
        int r = n - 1;
        bool an = true;
        while (l < r) {
            if (s[l] != s[r])an = false;
            l++;
            r--;

        }
        return an ? 1 : 2;
    }
};
