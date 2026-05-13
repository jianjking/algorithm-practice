#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<set>
using namespace std;
#define lson (idx << 1)
#define rson (idx << 1 | 1)
struct {
    int l, r, hi, lazy;
} s[100005 << 2];

void build(int idx, int l, int r) {
    s[idx].l = l, s[idx].r = r;
    s[idx].hi = 0, s[idx].lazy = 0;
    if (l < r) {
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
    }
}

void calc(int idx) {
    s[idx].hi = max(s[lson].hi, s[rson].hi);
}

void push_down(int idx) {
    if (s[idx].lazy != 0) {
        for (int i = lson; i <= rson; ++i) {
            s[i].hi += s[idx].lazy;
            s[i].lazy += s[idx].lazy;
        }
        s[idx].lazy = 0;
    }
}

void add(int idx, int l, int r, int val) {
    if (s[idx].l >= l && s[idx].r <= r) {
        s[idx].hi += val;
        s[idx].lazy += val;
    }
    else {
        push_down(idx);
        int mid = (s[idx].l + s[idx].r) >> 1;
        if (mid >= l)
            add(lson, l, r, val);
        if (mid < r)
            add(rson, l, r, val);
        calc(idx);
    }
}

int query(int idx, int l, int r) {
    if (s[idx].l >= l && s[idx].r <= r) {
        return s[idx].hi;
    }
    else {
        push_down(idx);
        int ans = 0;
        int mid = (s[idx].l + s[idx].r) >> 1;
        if (mid >= l)
            ans = max(ans, query(lson, l, r));
        if (mid < r)
            ans = max(ans, query(rson, l, r));
        return ans;
    }
}

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int l = 1e9, r = -1e9, d = 1e9, u = -1e9;
        long long area = 0;
        set<int> xs, ys;
        for (auto& rectangle : rectangles) {
            int li = rectangle[0], ri = rectangle[2], di = rectangle[1], ui = rectangle[3];
            l = min(l, li), r = max(r, ri), d = min(d, di), u = max(u, ui);
            area += 1LL * (ui - di) * (ri - li);
            xs.insert(li), xs.insert(ri), ys.insert(di), ys.insert(ui);
        }

        long long total_area = 1LL * (u - d) * (r - l);

        if (area != total_area)
            return false;

        int idx = 1;
        unordered_map<int, int> xmp, ymp;
        for (int xi : xs)
            xmp[xi] = idx++;
        idx = 1;
        for (int yi : ys)
            ymp[yi] = idx++;

        vector<vector<int>> sy(idx), ey(idx);
        for (int i = 0; i < rectangles.size(); ++i) {
            int di = rectangles[i][1], ui = rectangles[i][3];
            sy[ymp[di]].push_back(i);
            ey[ymp[ui]].push_back(i);
        }

        build(1, 1, xs.size());

        for (int i = 1; i < idx; ++i) {
            for (int j : ey[i]) {
                int li = rectangles[j][0], ri = rectangles[j][2];
                add(1, xmp[li], xmp[ri] - 1, -1);
            }
            for (int j : sy[i]) {
                int li = rectangles[j][0], ri = rectangles[j][2];
                add(1, xmp[li], xmp[ri] - 1, 1);
            }
            if (query(1, 1, xs.size()) > 1)
                return false;
        }

        return true;
    }
};

