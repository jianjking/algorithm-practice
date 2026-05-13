#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
using namespace std;

// Fenwick/树状数组 操作
void bit_add(int i, int v, vector<int>& bit) {
    int n = bit.size();
    for (; i < n; i += i & -i)
        bit[i] += v;
}

int bit_sum(int i, vector<int>& bit) {
    int s = 0;
    for (; i > 0; i -= i & -i)
        s += bit[i];
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // 下标 1…n
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cnt[i];
    }

    int m;
    cin >> m;
    // 存储所有查询：L, R, 原始索引
    vector<array<int, 3>> qs(m);
    for (int i = 0; i < m; i++) {
        cin >> qs[i][0] >> qs[i][1];  // L, R
        qs[i][2] = i;                 // 原始顺序
    }
    // 按 R 从小到大排序
    sort(qs.begin(), qs.end(), [](auto& A, auto& B) {
        return A[1] < B[1];
        });

    vector<int> bit(n + 1, 0);
    // 值的“上一次出现位置”，值域假设 ≤1e6
    vector<int> last_pos(1'000'001, 0);
    vector<int> ans(m);

    int r = 0;
    // 扫描所有查询
    for (auto& q : qs) {
        int L = q[0], R = q[1], idx = q[2];
        // 把右指针从 r 推到 R
        while (r < R) {
            ++r;
            int x = cnt[r];
            // 如果之前出现过，就在旧位置减 1
            if (last_pos[x] != 0) {
                bit_add(last_pos[x], -1, bit);
            }
            // 在当前位置加 1
            bit_add(r, +1, bit);
            last_pos[x] = r;
        }
        // 查询区间 [L, R] 内不同数的个数
        ans[idx] = bit_sum(R, bit) - bit_sum(L - 1, bit);
    }

    // 按原始顺序输出答案
    for (int v : ans) {
        cout << v << "\n";
    }
    return 0;
}
