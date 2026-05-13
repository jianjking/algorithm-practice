#include<iostream>
#include<vector>
using namespace std;

int main() {
    string s;
    cin >> s;
    // 预处理字符串，插入特殊字符'#'
    string tmp = "#";
    for (auto c : s) {
        tmp += c;
        tmp += "#";
    }
    int n = tmp.size();
    vector<int> l(n); // l[j]: 分割点j左侧能覆盖到的最长回文半径
    vector<int> r(n); // r[j]: 分割点j右侧能覆盖到的最长回文半径
    vector<int> p(n); // Manacher算法中的回文半径数组

    // Manacher算法计算每个位置的回文半径
    for (int i = 0, max_r = 0, c = 0; i < n; i++) {
        // 初始化回文半径，利用对称性加速
        int len = (max_r > i) ? min(max_r - i, p[2 * c - i]) : 1;
        // 中心扩展
        while (i - len >= 0 && i + len < n && tmp[i - len] == tmp[i + len]) {
            len++;
        }
        // 更新最右边界和中心
        if (i + len > max_r) {
            max_r = i + len;
            c = i;
        }
        p[i] = len;
    }

    // 计算l数组：预处理每个偶数分割点的左侧最大回文
    for (int i = 0, j = 0; i < n; i++) {
        // 遍历所有中心i，处理覆盖的分割点j
        while (i + p[i] >= j) {
            l[j] = j - i; // 左侧回文半径为j到中心i的距离
            j += 2; // 只处理偶数位置的分割点
        }
    }

    // 计算r数组：预处理每个偶数分割点的右侧最大回文
    for (int i = n - 1, j = n - 1; i >= 0; i--) {
        // 逆序遍历中心i，处理覆盖的分割点j
        while (i - p[i] <= j) {
            r[j] = i - j; // 右侧回文半径为分割点到中心i的距离
            j -= 2; // 只处理偶数位置的分割点
        }
    }

    int ans = 0;
    // 遍历所有有效分割点，求最大双回文长度
    for (int i = 2; i < n - 1; i += 2) {
        // 原字符串长度转换：半径-1 后相加
        ans = max(ans, l[i] + r[i] - 2);
    }
    cout << ans;
    return 0;
}