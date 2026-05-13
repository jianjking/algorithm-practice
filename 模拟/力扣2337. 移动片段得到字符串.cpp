#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool canChange(string start, string target) {
        int n = start.size();
        string s1, s2;
        vector<int>s3;
        vector<int>s4;
        s3.reserve(n);
        s4.reserve(n);
        for (int i = 0;i < n;i++) {
            if (start[i] != '_') {
                s3.push_back(i);
                s1 += start[i];
            }
            if (target[i] != '_') {
                s4.push_back(i);
                s2 += target[i];
            }
        }
        if (s1 != s2)return false;
        for (int i = 0;i < s3.size();i++) {
            if ((s3[i] < s4[i] && s1[i] == 'L') || (s3[i] > s4[i] && s1[i] == 'R'))return false;
        }
        return true;
    }
};