#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    string pushDominoes(string dominoes) {
        string s = "L" + dominoes + "R"; // 前后各加一个哨兵（不加哨兵的写法见另一份代码）
        int n = s.size();
        int pre = 0; // 上一个 L 或 R 的位置
        for (int i = 1; i < n; i++) {
            if (s[i] == '.') {
                continue;
            }
            if (s[i] == s[pre]) { // L...L 或 R...R
                fill(s.begin() + pre + 1, s.begin() + i, s[i]); // 全变成 s[i]
            }
            else if (s[i] == 'L') { // R...L
                fill(s.begin() + pre + 1, s.begin() + (pre + i + 1) / 2, 'R'); // 前一半变 R
                fill(s.begin() + (pre + i) / 2 + 1, s.begin() + i, 'L'); // 后一半变 L
            }
            pre = i;
        }
        return s.substr(1, n - 2); // 去掉前后哨兵
    }
};

