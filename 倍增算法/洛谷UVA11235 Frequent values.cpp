#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0) break;

        vector<int> nums(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> nums[i];
        }

        vector<int> l, r, cnt, tong(n + 1);
        int num = 1;
        l.push_back(1);
        for (int i = 2; i <= n; ++i) {
            if (nums[i] != nums[i - 1]) {
                r.push_back(i - 1);
                cnt.push_back(num);
                l.push_back(i);
                num = 0;
            }
            ++num;
            tong[i] = cnt.size() + 1;  // ¶Î±àºÅ´Ó 1 ¿ªÊ¼
        }
        r.push_back(n);
        cnt.push_back(num);

        // Sparse Table
        int limit = cnt.size();
        vector<int> lg(limit + 1);
        for (int i = 2; i <= limit; ++i) {
            lg[i] = lg[i >> 1] + 1;
        }

        int K = lg[limit] + 1;
        vector<vector<int>> st(limit + 1, vector<int>(K));
        for (int i = 1; i <= limit; ++i) st[i][0] = cnt[i - 1];
        for (int j = 1; j < K; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= limit; ++i) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }

        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            int c = tong[a];
            int d = tong[b];

            if (c == d) {
                cout << b - a + 1 << "\n";
            }
            else if (d == c + 1) {
                cout << max(r[c - 1] - a + 1, b - l[d - 1] + 1) << "\n";
            }
            else {
                int tmp = lg[d - c - 1];
                int max_mid = max(st[c + 1][tmp], st[d - (1 << tmp)][tmp]);
                int left_len = r[c - 1] - a + 1;
                int right_len = b - l[d - 1] + 1;
                cout << max({ left_len, right_len, max_mid }) << "\n";
            }
        }
    }
}