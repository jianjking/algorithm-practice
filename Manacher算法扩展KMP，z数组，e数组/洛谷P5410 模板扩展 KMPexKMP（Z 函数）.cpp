#include <iostream>
#include <vector>
using namespace std;

int main() {
    string a;    // 文本串 a
    string b;    // 模式串 b
    cin >> a >> b;

    int n = b.size();
    vector<int> z(n, 0);
    z[0] = n;    // z[0] 定义为整个字符串长度

    // —— 1. 计算模式串 b 的 Z 数组 ——
    // r 表示当前 Z-box 的右端点（下一个位置），c 表示 Z-box 的左端点
    for (int i = 1, r = 1, c = 1; i < n; i++) {
        // 如果 i 在 [c, r) 区间内，就可以利用之前计算过的值
        int len = (r > i) ? min(r - i, z[i - c]) : 0;

        // 从 len 开始，继续暴力匹配 b[len] 和 b[i+len]
        while (len + i < n && b[i + len] == b[len]) {
            len++;
        }

        // 如果新匹配区间超出了原来的 [c, r)，就更新 c, r
        if (len + i > r) {
            r = i + len;
            c = i;
        }

        z[i] = len;  // 存储 z[i] 值
    }

    // —— 2. 利用模式串的 Z 数组，在文本串 a 中做匹配 ——
    int m = a.size();
    vector<int> e(m, 0);
    // 重新用 r, c 表示在 a 上的匹配窗口
    for (int i = 0, r = 0, c = 0; i < m; i++) {
        // 如果 i 在当前窗口内，先取最小可能匹配长度
        int len = (r > i) ? min(r - i, z[i - c]) : 0;

        // 从 len 开始，继续暴力匹配 a[i+len] 和 b[len]
        while (len + i < m && len < n && a[i + len] == b[len]) {
            len++;
        }

        // 如果新匹配区间超出了原来的 [c, r)，就更新 c, r
        if (i + len > r) {
            r = i + len;
            c = i;
        }

        e[i] = len;  // 存储 e[i] 值
    }

    // —— 3. 按题目要求，用按位或计算两个答案 ——
    long long ans1 = 0;
    // 对模式串 z 数组贡献的部分
    for (int i = 0; i < n; i++) {
        // (i+1) * (z[i]+1) 相乘后再按位或累加
        ans1 |= (long long)(i + 1) * (z[i] + 1);
    }
    cout << ans1 << endl;

    long long ans2 = 0;
    // 对文本串匹配结果 e 数组贡献的部分
    for (int i = 0; i < m; i++) {
        ans2 |= (long long)(i + 1) * (e[i] + 1);
    }
    cout << ans2;

    return 0;
}
