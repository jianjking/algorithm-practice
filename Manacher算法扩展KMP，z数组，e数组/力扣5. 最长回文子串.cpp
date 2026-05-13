#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    string longestPalindrome(string s) {
        // 预处理字符串，插入特殊字符'#'，将奇偶长度回文统一处理
        string tmp = "#";
        for (int i = 0; i < s.size(); i++) {
            tmp += s[i];
            tmp += "#";
        }

        int mx = INT_MIN;    // 记录最长回文半径（预处理字符串中的半径）
        int end;             // 记录最长回文在原始字符串中的结尾位置
        int n = tmp.size();  // 预处理后的字符串长度
        vector<int> m(n);    // 记录每个中心点的回文半径

        // Manacher算法核心逻辑
        for (int i = 0, r = 0, c = 0; i < n; i++) {
            // 计算初始回文半径：利用对称性快速初始化
            int len = (r > i) ? min(r - i, m[2 * c - i]) : 1;

            // 中心扩展：尝试扩大回文半径
            while (i + len < n && i - len >= 0 && tmp[i + len] == tmp[i - len]) {
                len++;
            }

            // 更新右边界和中心点（维护最右回文区间）
            if (i + len > r) {
                r = i + len;
                c = i;
            }

            m[i] = len;  // 记录当前中心点的回文半径

            // 更新最长回文信息（关键修正点：原字符串实际长度为 len-1）
            if (len > mx) {
                mx = len;  // 预处理字符串中的半径
                end = (i + len - 1) / 2;  // 换算到原始字符串的结束位置
            }
        }

        // 计算起始位置并截取子串（修正公式：end - (mx-1) 即为起始索引）
        return s.substr(end - mx + 1, mx - 1);  // 参数：(起始位置, 长度)
    }
};