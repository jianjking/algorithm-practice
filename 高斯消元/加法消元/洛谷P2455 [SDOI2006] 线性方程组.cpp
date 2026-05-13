#include<iostream>
#include<vector>
using namespace std;

const double EPS = 1e-7;

int gauss(vector<vector<double>>& a, vector<double>& ans) {
    int n = (int)a.size() - 1;      // 1..n
    int m = (int)a[0].size() - 1;   // 1..(n+1)  增广列在 m (= n+1)
    int row = 1, col = 1;           // 当前处理到的行、列
    vector<int> where(n + 1, -1);   // 记录每一列的主元所在行

    while (row <= n && col <= n) {
        // 1) 在 [row..n] 中选 |a[r][col]| 最大的主元行
        int sel = row;
        for (int r = row; r <= n; ++r) {
            if (fabs(a[r][col]) > fabs(a[sel][col])) sel = r;
        }
        if (fabs(a[sel][col]) <= EPS) { // 这一列全≈0，换下一列
            ++col;
            continue;
        }
        swap(a[row], a[sel]);
        where[col] = row;

        // 2) 规范化：把主元行除以主元
        double piv = a[row][col];
        for (int j = col; j <= m; ++j) a[row][j] /= piv;

        // 3) 对其它行做消元（Gauss-Jordan，得到接近 RREF）
        for (int r = 1; r <= n; ++r) if (r != row) {
            double factor = a[r][col];          // 这里主元已经是 1
            if (fabs(factor) > EPS) {
                for (int j = col; j <= m; ++j) a[r][j] -= factor * a[row][j];
            }
        }
        ++row; ++col;
    }

    // 4) 检查矛盾行：系数全≈0 但常数项不≈0
    for (int r = 1; r <= n; ++r) {
        bool allZero = true;
        for (int c = 1; c <= n; ++c) if (fabs(a[r][c]) > EPS) { allZero = false; break; }
        if (allZero && fabs(a[r][n + 1]) > EPS) return -1; // 无解
    }

    // 5) 判断主元数量
    int rankA = 0;
    for (int c = 1; c <= n; ++c) if (where[c] != -1) ++rankA;
    if (rankA < n) return 0; // 多解（存在自由变量）

    // 6) 提取唯一解
    ans.assign(n + 1, 0.0);
    for (int c = 1; c <= n; ++c) {
        int r = where[c];
        ans[c] = (r != -1) ? a[r][n + 1] : 0.0;
    }
    return 1; // 唯一解
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<vector<double>> a(n + 1, vector<double>(n + 2, 0.0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n + 1; ++j) cin >> a[i][j];
    }

    vector<double> x;
    int typ = gauss(a, x);
    if (typ == -1) {
        cout << -1 << '\n';
        return 0;
    }
    if (typ == 0) {
        cout << 0 << '\n';
        return 0;
    }
    cout.setf(std::ios::fixed);
    cout << setprecision(2);
    for (int i = 1; i <= n; ++i) {
        // 把 -0.00 规避一下
        if (fabs(x[i]) < 0.5 * 1e-6) x[i] = 0;
        cout << "x" << i << "=" << x[i] << '\n';
    }
    return 0;
}
