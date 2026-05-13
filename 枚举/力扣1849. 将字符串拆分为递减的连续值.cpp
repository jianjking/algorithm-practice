#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;
class Solution {
public:
    bool splitString(string s) {
        long long start = 0;
        long long INF = 1e10; // 子串对应数值的上限
        int n = s.size();
        // 枚举第一个子字符串对应的初始值
        // 第一个子字符串不能包含整个字符串
        for (int i = 0; i < n - 1 && start < INF; ++i) {
            start = start * 10 + (s[i] - '0');
            // 循环验证当前的初始值是否符合要求
            long long pval = start;
            long long cval = 0;
            int cidx = i + 1;
            for (int j = i + 1; j < n && cval < INF; ++j) {
                if (pval == 1) {
                    // 如果上一个值为 1，那么剩余字符串对应的数值只能为 0
                    if (all_of(s.begin() + cidx, s.end(), [](char c) { return c == '0'; })) {
                        return true;
                    }
                    else {
                        break;
                    }
                }
                cval = cval * 10 + (s[j] - '0');
                if (cval > pval - 1) {
                    // 不符合要求，提前结束
                    break;
                }
                else if (cval == pval - 1) {
                    if (j + 1 == n) {
                        // 已经遍历到末尾
                        return true;
                    }
                    pval = cval;
                    cval = 0;
                    cidx = j + 1;
                }
            }
        }
        return false;
    }
};