#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    string smallestNumber(string pattern) {
        int n = pattern.length();
        string ans;
        for (int i = 1; i <= n + 1; i++) ans += to_string(i);
        int i = 0;
        while (i < n) {
            if (pattern[i] == 'I') {
                i++;
                continue;
            }
            int i0 = i;
            for (i++; i < n && pattern[i] == 'D'; i++) {
            }
            reverse(ans.begin() + i0, ans.begin() + i + 1);
        }
        return ans;
    }
};