#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    long long numberOfSubstrings(string s) {
        int n = s.size();
        vector<int> f(3, 0);
        long long miss = 0;                       // 统计“缺 a/b/c 中至少一者”的子串数
        long long total = 1LL * n * (n + 1) / 2;  // 总子串数

        int r = 0;
        for (int l = 0; l < n; l++) {
            // 将 r 向右扩，直到 [l, r) 第一次覆盖 a,b,c 三个字符，或到达末尾
            while (r < n && !(f[0] && f[1] && f[2])) {
                f[s[r] - 'a']++;
                r++;
            }
            if (f[0] && f[1] && f[2]) {
                // 找到第一个合法窗口 [l, r)
                // 不全含 a/b/c 的，右端点只能放在 l…(r-1)-1，共 (r-1) - l = r-l-1 个
                miss += (r - l - 1);
            }
            else {
                // 即使拉到了末尾，依然不全含，说明所有以 l 开头的子串都不合法
                miss += (n - l);
            }
            // 窗口左端收缩
            f[s[l] - 'a']--;
        }

        // 含 a,b,c 三个字符的子串 = 总子串数 - 缺至少一个的子串数
        return total - miss;
    }
};
