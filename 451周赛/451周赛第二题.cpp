#include<iostream>
#include<vector>
#include<deque>
using namespace std;
class Solution {
public:
    string resultingString(string s) {
        int n = s.size();
   
        deque<char>f;
        for (int i = 0;i < n;i++) {
            if (f.empty()) {
                f.push_back(s[i]);
                continue;
             }
            char a = f.back();
            if ((a == 'z' && s[i] == 'a') || (a == 'a' && s[i] == 'z') || (a == s[i] + 1) || s[i] == a + 1)f.pop_back();
            else {
                f.push_back(s[i]);
            }
        }
        string ans;
        while (!f.empty()) {
            ans += f.front();
            f.pop_front();
        }
        return ans;

    }
};