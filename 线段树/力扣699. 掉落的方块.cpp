#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<int> mx, lz;
vector<bool> visit_flag;

// 在 idx 节点上设置值 val
void apply(int idx, int val) {
    mx[idx] = val;
    lz[idx] = val;
    visit_flag[idx] = true;
}

// 下推懒标记
void push_down(int idx) {
    if (visit_flag[idx]) {
        apply(idx * 2, lz[idx]);
        apply(idx * 2 + 1, lz[idx]);
        visit_flag[idx] = false;
    }
}

// 向上更新
void pull_up(int idx) {
    mx[idx] = max(mx[idx * 2], mx[idx * 2 + 1]);
}

// 区间更新 [L, R] 赋值为 val
void update(int L, int R, int val, int l, int r, int idx) {
    if (L <= l && r <= R) {
        apply(idx, val);
        return;
    }
    push_down(idx);
    int mid = (l + r) / 2;
    if (L <= mid) update(L, R, val, l, mid, idx * 2);
    if (R > mid) update(L, R, val, mid + 1, r, idx * 2 + 1);
    pull_up(idx);
}

// 区间查询最大值
int query(int L, int R, int l, int r, int idx) {
    if (L <= l && r <= R) {
        return mx[idx];
    }
    push_down(idx);
    int mid = (l + r) / 2;
    int res = 0;
    if (L <= mid) res = max(res, query(L, R, l, mid, idx * 2));
    if (R > mid) res = max(res, query(L, R, mid + 1, r, idx * 2 + 1));
    return res;
}

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> xs;
        xs.reserve(n * 2);
        for (auto& p : positions) {
            xs.push_back(p[0]);
            xs.push_back(p[0] + p[1] - 1);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int m = xs.size();
        mx.assign(4 * m + 5, 0);
        lz.assign(4 * m + 5, 0);
        visit_flag.assign(4 * m + 5, false);

        vector<int> ans;
        ans.reserve(n);
        int global_max = 0;

        for (auto& p : positions) {
            int L = lower_bound(xs.begin(), xs.end(), p[0]) - xs.begin() + 1;
            int R = lower_bound(xs.begin(), xs.end(), p[0] + p[1] - 1) - xs.begin() + 1;
            int base = query(L, R, 1, m, 1);
            update(L, R, base + p[1], 1, m, 1);
            global_max = max(global_max, base + p[1]);
            ans.push_back(global_max);
        }
        return ans;
    }
};
