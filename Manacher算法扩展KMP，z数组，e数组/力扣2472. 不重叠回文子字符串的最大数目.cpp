#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    // 核心查找函数：从位置l开始寻找第一个满足长度>=k的回文，返回其右边界下一个#的位置
    // 参数：
    // l: 当前查找的起始位置（在预处理后的字符串tmp中）
    // tmp: 预处理后的字符串（原字符间插入#）
    // limit: 原字符串要求回文的最小长度k
    // 返回值：找到的回文右边界下一个#的位置，若找不到返回-1
    int f(int l, string& tmp, int limit) {
        vector<int> p(tmp.size(), 0); // 回文半径数组
        int n = tmp.size();
        // Manacher算法核心逻辑：动态计算每个位置的回文半径
        for (int i = l, r = l, c = l; i < n; i++) {
            // 初始回文半径（利用对称性加速）
            int len = r > i ? min(r - i, p[2 * c - i]) : 1;
            // 尝试扩展回文半径（需满足左边界>=l，避免重叠）
            while (i - len >= l && i + len < n && tmp[i - len] == tmp[i + len]) {
                len++;
                // 发现回文半径超过k时立即处理（此时原字符串长度>=k）
                if (len > limit) {
                    // 确保返回的位置是#，否则调整到下一个#
                    return tmp[i + limit] == '#' ? i + limit : i + limit + 1;
                }
            }
            // 更新最右回文边界及其中心
            if (i + len > r) {
                r = len + i;
                c = i;
            }
            p[i] = len; // 记录当前中心的回文半径
        }
        return -1; // 未找到满足条件的回文
    }

    // 主函数：计算最大不重叠回文子串数目
    int maxPalindromes(string s, int k) {
        if (k == 1) return s.size(); // 特判k=1时可全分割
        // 预处理原字符串，构造处理后的字符串tmp（如abc -> #a#b#c#）
        string tmp = "#";
        for (int i = 0; i < s.size(); i++) {
            tmp += s[i];
            tmp += "#";
        }
        int ans = 0;
        int l = 0; // 当前查找的起始位置
        // 循环查找所有不重叠回文
        while ((l = f(l, tmp, k)) != -1) {
            ans++; // 找到一个回文，计数增加
        }
        return ans;
    }
};