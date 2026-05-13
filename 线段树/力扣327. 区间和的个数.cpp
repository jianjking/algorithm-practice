#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct SegTree {
    int n;
    vector<int> t;
    SegTree(int n = 0) : n(n), t(4 * n + 5, 0) {}

    void add(int idx, int l, int r, int p) {
        if (l == r) { t[idx]++; return; }
        int m = (l + r) >> 1;
        if (p <= m) add(idx << 1, l, m, p);
        else add(idx << 1 | 1, m + 1, r, p);
        t[idx] = t[idx << 1] + t[idx << 1 | 1];
    }
    void add(int p) { add(1, 1, n, p); }

    int query(int idx, int l, int r, int ql, int qr) {
        if (ql > qr) return 0;
        if (ql <= l && r <= qr) return t[idx];
        int m = (l + r) >> 1, ans = 0;
        if (ql <= m) ans += query(idx << 1, l, m, ql, qr);
        if (qr > m) ans += query(idx << 1 | 1, m + 1, r, ql, qr);
        return ans;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

class Solution {
public:
    long long countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = (int)nums.size();
        // 1) 前缀和（long long）
        vector<long long> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + (long long)nums[i - 1];

        // 2) 坐标压缩（只压前缀和本身；边界用二分找）
        vector<long long> all = pre;
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());

        auto get_id = [&](long long x)->int {
            // 压缩到 [1..all.size()]
            int id = (int)(lower_bound(all.begin(), all.end(), x) - all.begin()) + 1;
            return id;
            };

        SegTree st((int)all.size());

        long long ans = 0;
        // 先放入 pre[0] = 0，使得区间从头就能匹配
        st.add(get_id(pre[0]));

        for (int i = 1; i <= n; ++i) {
            long long L = pre[i] - upper; // 注意：是 -upper
            long long R = pre[i] - lower; // 注意：是 -lower

            // 在有序 all 上找 [L, R] 的下标范围
            int lpos = (int)(lower_bound(all.begin(), all.end(), L) - all.begin()) + 1;
            int rpos = (int)(upper_bound(all.begin(), all.end(), R) - all.begin()); // 返回的是>R的first，再-1
            // rpos 当前是以 0 为基的索引；+1 之后等于压缩坐标
            // 但我们已在 +1 前做了 upper_bound，所以这里不 +1
            // 统一成压缩坐标区间：[lpos, rpos]

            if (lpos <= rpos) ans += st.query(lpos, rpos);

            // 再把当前 pre[i] 放进树，下轮用于“之前前缀”的统计
            st.add(get_id(pre[i]));
        }
        return ans;
    }
};
