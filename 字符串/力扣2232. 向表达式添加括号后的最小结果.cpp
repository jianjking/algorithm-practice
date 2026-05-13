#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
class Solution {
public:
    string minimizeResult(string expression) {
        int idx;
        int n = expression.size();
        for (int i = 0;i < n;i++) {
            if (expression[i] == '+') {
                idx = i;
            }
        }
        int sum = INT_MAX;
        int a;int b;
        string s1 = expression.substr(0, idx);
        string s2 = expression.substr(idx + 1, n);
        for (int i = 0;i < s1.size();i++) {
            for (int j = 1;j <= s2.size();j++) {
                int num1 = 1;
                int num2 = 1;
                if (i != 0)num1 = atoi(s1.substr(0, i).c_str());
                int num3 = atoi(s1.substr(i, s1.size()).c_str());
                num3 += atoi(s2.substr(0, j).c_str());
                if (j != s2.size())num2 = atoi(s2.substr(j, s2.size()).c_str());
                if (num3 * num1 * num2 < sum) {
                    sum = num3 * num1 * num2;
                    a = i;
                    b = j;
                }
            }
        }
        string res;
        for (int i = 0;i < n;i++) {
            if (i == a)res += '(';
            res += expression[i];
            if (i == b + idx)res += ')';
        }
        return res;
    }
};