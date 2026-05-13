#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long;

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int repeatCount = n1;
        int L = s1.size();

        // 构造 nxt 数组：从 i 位置开始，跳到下一个字符 c 需要的步长（含匹配字符）
        vector<vector<int>> nxt(L, vector<int>(26, -1));
        vector<int> pre(26, -1);
        for (int i = L - 1; i >= 0; --i)
            pre[s1[i] - 'a'] = i + L;
        for (int i = L - 1; i >= 0; --i) {
            pre[s1[i] - 'a'] = i;
            for (int c = 0; c < 26; ++c)
                if (pre[c] != -1)
                    nxt[i][c] = pre[c] - i + 1;
        }
        // 如果 s2 中有字符永远找不到，直接 0
        for (char c : s2)
            if (nxt[0][c - 'a'] == -1) return 0;

        const int MAXP = 31;
        // st[i][p] = 从 s1[i] 出发，匹配 2^p 个 s2 一共消耗的字符数（相对消耗）
        vector<vector<ll>> st(L, vector<ll>(MAXP, 0));

        // p=0：一次匹配 s2 的消耗
        for (int i = 0; i < L; ++i) {
            ll cur = i;
            for (char c : s2)
                cur += nxt[cur % L][c - 'a'];
            st[i][0] = cur - i;
        }

        // 倍增
        for (int p = 1; p < MAXP; ++p) {
            for (int i = 0; i < L; ++i) {
                ll consumed = st[i][p - 1];
                int nxtIdx = (i + consumed) % L;
                st[i][p] = consumed + st[nxtIdx][p - 1];
            }
        }

        // 二分倍增算总共能匹配多少次 s2
        ll used = 0, cnt = 0, limit = ll(repeatCount) * L;
        for (int p = MAXP - 1; p >= 0; --p) {
            int idx = used % L;
            if (used + st[idx][p] <= limit) {
                used += st[idx][p];
                cnt += (1LL << p);
            }
        }
        return cnt / n2;
    }
};

int main() {
    Solution sol;
    cout << sol.getMaxRepetitions("aaa", 3, "aa", 1) << "\n"; // 4
    return 0;
}
