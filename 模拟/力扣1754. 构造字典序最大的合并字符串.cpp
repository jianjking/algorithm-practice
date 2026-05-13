#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string largestMerge(string word1, string word2) {
        string s;
        int n = word1.size();
        int m = word2.size();
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (word1[i] > word2[j]) {
                s += word1[i++];
            } else if (word1[i] < word2[j]) {
                s += word2[j++];
            } else {
                // 关键修正：比较两个后缀的字典序
                if (word1.compare(i, n - i, word2, j, m - j) > 0) {
                    s += word1[i++];
                } else {
                    s += word2[j++];
                }
            }
        }
        while (i < n) s += word1[i++];
        while (j < m) s += word2[j++];
        return s;
    }
};
