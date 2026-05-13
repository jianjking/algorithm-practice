#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const double eps = 1e-7;

    while (true) {
        int n, k;
        if (!(cin >> n >> k)) break;
        if (n == 0 && k == 0) break;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        // 上界：max a[i]/b[i]（避免无谓的巨大搜索区间）
        double l = 0.0, r = 0.0;
        for (int i = 0; i < n; i++) {
            if (b[i] > 0) r = max(r, a[i] / (double)b[i]);
        }
        // 如果题目保证 a<=b，可直接 r=1.0

        vector<double> tmp(n);
        auto ok = [&](double mid) -> bool {
            for (int i = 0; i < n; i++) tmp[i] = a[i] - mid * b[i];
            // 取前 n-k 大
            nth_element(tmp.begin(), tmp.begin() + (n - k), tmp.end(), greater<double>());
            double sum = 0.0;
            for (int i = 0; i < n - k; i++) sum += tmp[i];
            return sum >= 0.0;
            };

        // 标准二分：维护 l 可行、r 不可行（或相反），这里维护 l 可行
        // 先保证 l 可行
        if (!ok(l)) {
            // 极端情况：如果连 0 都不可行（一般题面不会这样），按需处理
            // 这里直接输出 0
            cout << 0 << '\n';
            continue;
        }

        while (r - l > eps) {
            double mid = (l + r) / 2.0;
            if (ok(mid)) l = mid;
            else r = mid;
        }

        // 四舍五入到百分数
        cout << (int)(l * 100.0 + 0.5) << '\n';
    }
    return 0;
}
r = mid;