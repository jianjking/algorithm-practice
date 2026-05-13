#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        vector<int>cnt(26, 0);
        int n = s.size();
        int m = t.size();
        if (m != n)return false;
        for (int i = 0;i < n;i++) {
            if (s[i] != t[i])cnt[(t[i] - s[i] + 26) % 26]++;
        }
        for (int i = 0;i < 26;i++) {
            if (cnt[i] > 0 && k < (i + (cnt[i] - 1) * 26))return false;
        }
        return true;
    }
};