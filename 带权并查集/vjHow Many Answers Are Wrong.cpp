#include <bits/stdc++.h>
using namespace std;

// w[x] = pre[fa[x]] - pre[x]
int find_root(int x, vector<int>& fa, vector<long long>& w) {
    if (fa[x] == x) return x;
    int p = fa[x];
    int f = find_root(p, fa, w);
    w[x] += w[p];
    return fa[x] = f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {                 // ① 多组数据直到 EOF
        int N = n + 1;                      // 节点 1..n+1（用 r+1）
        vector<int> fa(N + 1);
        vector<long long> w(N + 1, 0);
        iota(fa.begin(), fa.end(), 0);

        int wrong = 0;
        for (int i = 0; i < m; i++) {
            int l, r; long long s;
            cin >> l >> r >> s;
            r += 1;                         // ② [l..r] -> (l, r+1)

            int fl = find_root(l, fa, w);
            int fr = find_root(r, fa, w);

            if (fl == fr) {                 // 同集合，校验
                if (w[l] - w[r] != s) ++wrong;
            } else {                        // 不同集合，按方向合并
                fa[fl] = fr;
                w[fl] = s + w[r] - w[l];    // ③ pre[fr] - pre[fl]
            }
        }
        cout << wrong << '\n';
    }
    return 0;
}
