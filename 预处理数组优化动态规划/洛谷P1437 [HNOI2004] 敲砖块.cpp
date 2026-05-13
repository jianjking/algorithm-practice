#include<iostream>
#include<vector>
using namespace std;

static const int NEG = INT_MIN / 4;
inline int tri(int x) { return x * (x + 1) / 2; }

int n, m;
vector<vector<int>> a;            // a[i][j] : 第 i 层第 j 块分值（0-based），长度 = n - i
vector<vector<int>> pref;         // pref[i][t] : 第 i 层前 t 个之和（pref[i][0]=0）
vector<vector<vector<int>>> dp;   // dp[i][j][k]

inline int row_prefix_sum(int i, int j) { return pref[i][j + 1]; }

int solve(int i, int j, int k) {
    int len_i = n - i;
    if (i < 0 || j < 0 || j >= len_i) return NEG;
    if (k < j + 1) return NEG;            // 本层拿到前缀 j 至少要 j+1 块

    int& memo = dp[i][j][k];
    if (memo != NEG) return memo;

    const int here = row_prefix_sum(i, j);

    if (i == 0) {
        // 顶层没有父层，恰好用 j+1 块才能拿到前缀 j
        return memo = (k == j + 1 ? here : NEG);
    }

    int best = NEG;
    int left = k - (j + 1);               // 留给 0..(i-1) 层的块数
    int max_z = n - i;                    // 上一层下标范围 0..(n-i)

    // ★关键修正：上一层至少取到“前缀 j+1（含）”，否则撑不住本层的 j
    for (int z = j + 1; z <= max_z; ++z) {
        int up = solve(i - 1, z, left);
        if (up == NEG) continue;
        best = max(best, here + up);
    }
    return memo = best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int total = tri(n);
    if (m > total) m = total;

    a.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int len = n - i;
        a[i].resize(len);
        for (int j = 0; j < len; ++j) cin >> a[i][j];
    }

    pref.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int len = n - i;
        pref[i].assign(len + 1, 0);
        for (int t = 1; t <= len; ++t) pref[i][t] = pref[i][t - 1] + a[i][t - 1];
    }

    dp.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int len = n - i;
        dp[i].assign(len, vector<int>(m + 1, NEG));
    }

    // “最多 m 块”——对 k=0..m 都试，取最大
    int ans = 0;
    for (int k = 0; k <= m; ++k) {
        for (int i = 0; i < n; ++i) {
            int len = n - i;
            for (int j = 0; j < len; ++j) {
                ans = max(ans, solve(i, j, k));
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
