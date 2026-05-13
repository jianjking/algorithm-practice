#include <iostream>
#include <vector>
using namespace std;

// 树状数组：单点加，前缀和查询
void add(int idx, long long val, vector<long long>& bit) {
    int n = bit.size();
    while (idx < n) {
        bit[idx] += val;
        idx += idx & -idx;
    }
}

long long querier(int idx, const vector<long long>& bit) {
    long long s = 0;
    while (idx > 0) {
        s += bit[idx];
        idx -= idx & -idx;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // 大小留到 n+2，方便处理 d+1 的更新
    vector<long long> tree1(n + 2, 0);
    vector<long long> tree2(n + 2, 0);

    // 初始化：把初始数组 A[i] 视为区间 [i,i] 加 A[i]
    for (int i = 1; i <= n; i++) {
        long long tmp;
        cin >> tmp;
        add(i, tmp, tree1);
        add(i + 1, -tmp, tree1);
        add(i, (i - 1) * tmp, tree2);
        add(i + 1, -(long long)i * tmp, tree2);
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            // 区间 [c, d] 增加 e
            int c, d;
            long long e;
            cin >> c >> d >> e;
            add(c, e, tree1);
            add(d + 1, -e, tree1);
            add(c, (c - 1) * e, tree2);
            add(d + 1, -(long long)d * e, tree2);
        }
        else if (op == 2) {
            // 区间和查询 [c, d]
            int c, d;
            cin >> c >> d;
            // 计算前缀和 S(x) = x*sum(bit1, x) - sum(bit2, x)
            auto prefix = [&](int x) -> long long {
                return (long long)x * querier(x, tree1)
                    - querier(x, tree2);
                };
            long long ans = prefix(d) - prefix(c - 1);
            cout << ans << "\n";
        }
    }

    return 0;
}
