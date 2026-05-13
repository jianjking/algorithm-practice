#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 比较函数：长度优先，其次字典序
    bool better(const string& s1, const string& s2) {
        if (s1.size() != s2.size()) return s1.size() < s2.size();
        return s1 < s2;
    }

    // 把两个字符串合成一个最短的，顺便考虑两种拼接方向
    string merge2(const string& a, const string& b) {
        // 如果一个已经包含另一个，直接返回较长的那个
        if (a.find(b) != string::npos) return a;
        if (b.find(a) != string::npos) return b;

        int n = (int)a.size();
        int m = (int)b.size();

        // a + b：让 a 的后缀 和 b 的前缀 尽量重叠
        int ov1 = 0;
        for (int k = min(n, m); k > 0; --k) {
            bool ok = true;
            for (int i = 0; i < k; ++i) {
                if (a[n - k + i] != b[i]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ov1 = k;
                break;
            }
        }
        string s1 = a + b.substr(ov1);

        // b + a：让 b 的后缀 和 a 的前缀 尽量重叠
        int ov2 = 0;
        for (int k = min(n, m); k > 0; --k) {
            bool ok = true;
            for (int i = 0; i < k; ++i) {
                if (b[m - k + i] != a[i]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ov2 = k;
                break;
            }
        }
        string s2 = b + a.substr(ov2);

        // 选更优的那个（长度优先，再比字典序）
        return better(s1, s2) ? s1 : s2;
    }

    // 按给定顺序合并三个字符串
    string build(const string& x, const string& y, const string& z) {
        return merge2(merge2(x, y), z);
    }

    string minimumString(string a, string b, string c) {
        string ans = build(a, b, c);

        // 枚举三字符串的 6 种排列
        vector<tuple<string,string,string>> orders = {
            {a, b, c},
            {a, c, b},
            {b, a, c},
            {b, c, a},
            {c, a, b},
            {c, b, a},
        };

        for (auto &t : orders) {
            string x, y, z;
            tie(x, y, z) = t;
            string cand = build(x, y, z);
            if (better(cand, ans)) ans = cand;
        }

        return ans;
    }
};
