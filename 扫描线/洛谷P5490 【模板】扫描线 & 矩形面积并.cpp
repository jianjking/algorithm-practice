#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
using ll = long long;

static const int MAXN = 200000 * 2 + 5;
static ll lng[MAXN * 4], cnt[MAXN * 4], cur[MAXN * 4];

void build(int l, int r, int i, const ll ys[]) {
    if (l == r) {
        // leaf covers [ys[l], ys[l+1]) so index goes from 1..totY-1
        lng[i] = ys[l + 1] - ys[l];
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i * 2, ys);
        build(mid + 1, r, i * 2 + 1, ys);
        lng[i] = lng[i * 2] + lng[i * 2 + 1];
    }
}

void up(int i, int l, int r) {
    if (cnt[i] > 0) {
        cur[i] = lng[i];
    }
    else if (l == r) {
        cur[i] = 0;
    }
    else {
        cur[i] = cur[i * 2] + cur[i * 2 + 1];
    }
}

void add(int a, int b, int v, int l, int r, int i) {
    if (b < l || a > r) return;
    if (a <= l && r <= b) {
        cnt[i] += v;
        if (cnt[i] > 0) cur[i] = lng[i];
        else if (l == r) cur[i] = 0;
        else cur[i] = cur[i * 2] + cur[i * 2 + 1];
    }
    else {
        int mid = (l + r) >> 1;
        add(a, b, v, l, mid, i * 2);
        add(a, b, v, mid + 1, r, i * 2 + 1);
        up(i, l, r);
    }
}

struct Event { ll x, y1, y2; int type; };
static Event events[MAXN];
static ll ys[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int totEv = 2 * n;
    int totY = 0;
    for (int i = 0; i < n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events[2 * i] = { x1, y1, y2, +1 };
        events[2 * i + 1] = { x2, y1, y2, -1 };
        ys[++totY] = y1;  // 1-based
        ys[++totY] = y2;
    }
    sort(ys + 1, ys + totY + 1);
    totY = unique(ys + 1, ys + totY + 1) - (ys + 1) + 1;
    sort(events, events + totEv, [](auto& a, auto& b) { return a.x < b.x; });

    // build segment tree over [1, totY-1]
    build(1, totY - 1, 1, ys);

    ll ans = 0;
    ll preX = events[0].x;
    for (int i = 0; i < totEv; ++i) {
        ll x = events[i].x;
        ll dx = x - preX;
        ans += cur[1] * dx;
        int l = lower_bound(ys + 1, ys + totY + 1, events[i].y1) - ys;
        int r = lower_bound(ys + 1, ys + totY + 1, events[i].y2) - ys - 1;
        if (l <= r) add(l, r, events[i].type, 1, totY - 1, 1);
        preX = x;
    }

    cout << ans;
    return 0;
}