#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// 求 BIT[1..i] 的前缀和，i 是 1-based
long long bit_sum(int i, const vector<int>& tree) {
    long long s = 0;
    while (i > 0) {
        s += tree[i];
        i -= i & -i;
    }
    return s;
}

// 0-based 查询区间 [l..r] 已删除的元素个数
long long query0(int l, int r, const vector<int>& tree) {
    if (l > r) return 0;
    // r+1 转成 1-based 的最后一个，l 转成 1-based 的前缀末
    return bit_sum(r + 1, tree) - bit_sum(l, tree);
}

// 在 0-based 位置 idx 上标记「已删除」(+1)
void add0(int idx, int v, vector<int>& tree) {
    // idx+1 转成 1-based
    int i = idx + 1;
    int n = tree.size();
    while (i < n) {
        tree[i] += v;
        i += i & -i;
    }
}

class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
        int n = nums.size();
        // tmp 存下标 0..n-1，按照 nums 值升序
        vector<int> tmp(n);
        iota(tmp.begin(), tmp.end(), 0);
        sort(tmp.begin(), tmp.end(), [&](int a, int b) {
            return nums[a] < nums[b];
            });

        // Fenwick Tree 大小 n+1（我们用 1..n）
        vector<int> tree(n + 1, 0);

        // 初始每次删除还要再加一次移动：ans = n
        long long ans = n;

        // pre 是上一次删除的位置，用 0-based，初始在 0
        int pre = 0;

        for (int idx : tmp) {
            int cur = idx;  // 0-based 要删除的位置
            if (cur >= pre) {
                // 正向走，跳过已经删掉的
                ans += (cur - pre)
                    - query0(pre, cur - 1, tree);
            }
            else {
                // 从末尾绕回
                ans += (n - pre)
                    - query0(pre, n - 1, tree);
                ans += cur
                    - query0(0, cur - 1, tree);
            }
            // 标记 cur 被删
            add0(cur, 1, tree);
            // 更新 pre
            pre = cur;
        }
        return ans;
    }
};
