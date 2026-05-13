#include<iostream>
#include<vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int BIT = 60;  // 覆盖到 2^50
    vector<unsigned long long> nums(n + 1, 0);

    for (int i = 1; i <= n; i++)
        cin >> nums[i];

    vector<int> where(BIT + 1, 0);
    int row = 1;

    // Gauss-Jordan：列从高到低，每找到主元，就把该列在所有行清零
    for (int col = BIT; col >= 0 && row <= n; col--) {
        int mx = -1;

        for (int r = row; r <= n; r++) {
            if ((nums[r] >> col) & 1ULL) {
                mx = r;
                break;
            }
        }

        if (mx == -1)
            continue;

        swap(nums[row], nums[mx]);

        for (int i = 1; i <= n; i++) {
            if (i != row && ((nums[i] >> col) & 1ULL))
                nums[i] ^= nums[row];
        }

        where[col] = row++;
    }

    int r = row - 1;                 // 线性基秩
    bool zero = (r != n);            // 有依赖 => 非空子集也能异或出 0

    // ★ 关键：按“主元列从低到高”收集基向量，使得索引位 j 对应 base[j]
    vector<unsigned long long> base;
    base.reserve(r);

    for (int col = 0; col <= BIT; ++col) {
        if (where[col])
            base.push_back(nums[where[col]]);
    }

    // 至此，base[0] 的主元位是最低，base[r-1] 的主元位最高

    // 合法答案个数
    unsigned long long total = zero ? (1ULL << r)
        : ((r ? (1ULL << r) : 0ULL) - 1ULL);

    int m;
    cin >> m;

    while (m--) {
        unsigned long long k;
        cin >> k;

        if (k < 1 || k > total) {
            cout << -1 << '\n';
            continue;
        }

        if (zero) {                 // 0 也在答案里，占第 1 小
            if (k == 1) {
                cout << 0 << '\n';
                continue;
            }

            --k;                    // 去掉 0，把 k 映射到 [0..2^r-1]
        }

        unsigned long long idx = k; // 满秩时：直接用 k（0 保留给空集）

        unsigned long long ans = 0;

        for (int j = 0; j < r; ++j) {
            if ((idx >> j) & 1ULL)
                ans ^= base[j];
        }

        cout << ans << '\n';
    }

    return 0;
}