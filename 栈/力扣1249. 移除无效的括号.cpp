#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string ans;
        stack<pair<char, int>>p;
        int n = s.size();
        for (int i = 0;i < n;i++) {
            if (s[i] == '(') {
                p.push({ '(', i });
            }
            else if (s[i] == ')') {
                if (p.empty())continue;
                pair<char, int>tmp = p.top();
                s[tmp.second] = '0';
                s[i] = '1';
                p.pop();
            }
        }
        for (auto& p : s)if (p != '(' && p != ')') {
            if (p == '0') {
                ans += '(';
            }
            else if (p == '1') {
                ans += ')';
            }
            else {
                ans += p;
            }
        }
        return ans;
    }
};