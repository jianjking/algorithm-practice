#include<iostream>
#include<vector>
#include<climits>
using namespace std;
typedef long long ll;
const ll NEG_INF = LLONG_MIN;

int n, m;
vector<ll> arr;
// segment tree arrays
vector<ll> segSum, segMax, segSem, segMaxAdd, segOAdd;
vector<ll> segMaxHist, segMaxAddHist, segOAddHist;
vector<int> segCnt;

void up(int i) {
    int l = i << 1, r = i << 1 | 1;
    // sum
    segSum[i] = segSum[l] + segSum[r];
    // max and second max & count
    segMaxHist[i] = max(segMaxHist[l], segMaxHist[r]);
    if (segMax[l] > segMax[r]) {
        segMax[i] = segMax[l];
        segCnt[i] = segCnt[l];
        segSem[i] = max(segSem[l], segMax[r]);
    }
    else if (segMax[l] < segMax[r]) {
        segMax[i] = segMax[r];
        segCnt[i] = segCnt[r];
        segSem[i] = max(segMax[l], segSem[r]);
    }
    else {
        segMax[i] = segMax[l];
        segCnt[i] = segCnt[l] + segCnt[r];
        segSem[i] = max(segSem[l], segSem[r]);
    }
}

void applyLazy(int i, int len, ll maxAddv, ll otherAddv, ll maxAddTopv, ll otherAddTopv) {
    // update history
    segMaxHist[i] = max(segMaxHist[i], segMax[i] + maxAddTopv);
    segMaxAddHist[i] = max(segMaxAddHist[i], segMaxAdd[i] + maxAddTopv);
    segOAddHist[i] = max(segOAddHist[i], segOAdd[i] + otherAddTopv);
    // apply to sum and max/sem
    segSum[i] += maxAddv * segCnt[i] + otherAddv * (len - segCnt[i]);
    segMax[i] += maxAddv;
    if (segSem[i] != NEG_INF) segSem[i] += otherAddv;
    segMaxAdd[i] += maxAddv;
    segOAdd[i] += otherAddv;
}

void down(int i, int l, int r) {
    int mid = (l + r) >> 1;
    int ls = i << 1, rs = i << 1 | 1;
    ll tmp = max(segMax[ls], segMax[rs]);
    if (segMax[ls] == tmp) {
        applyLazy(ls, mid - l + 1, segMaxAdd[i], segOAdd[i], segMaxAddHist[i], segOAddHist[i]);
    }
    else {
        applyLazy(ls, mid - l + 1, segOAdd[i], segOAdd[i], segOAddHist[i], segOAddHist[i]);
    }
    if (segMax[rs] == tmp) {
        applyLazy(rs, r - mid, segMaxAdd[i], segOAdd[i], segMaxAddHist[i], segOAddHist[i]);
    }
    else {
        applyLazy(rs, r - mid, segOAdd[i], segOAdd[i], segOAddHist[i], segOAddHist[i]);
    }
    segMaxAdd[i] = segOAdd[i] = segMaxAddHist[i] = segOAddHist[i] = 0;
}

void build(int l, int r, int i) {
    segMaxAdd[i] = segOAdd[i] = segMaxAddHist[i] = segOAddHist[i] = 0;
    if (l == r) {
        segSum[i] = segMax[i] = segMaxHist[i] = arr[l];
        segSem[i] = NEG_INF;
        segCnt[i] = 1;
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void updateAdd(int l, int r, ll v, int nl, int nr, int i) {
    if (l <= nl && nr <= r) {
        applyLazy(i, nr - nl + 1, v, v, v, v);
    }
    else {
        down(i, nl, nr);
        int mid = (nl + nr) >> 1;
        if (l <= mid) updateAdd(l, r, v, nl, mid, i << 1);
        if (r > mid)  updateAdd(l, r, v, mid + 1, nr, i << 1 | 1);
        up(i);
    }
}

void updateMin(int l, int r, ll v, int nl, int nr, int i) {
    if (v >= segMax[i]) return;
    if (l <= nl && nr <= r && segSem[i] < v) {
        applyLazy(i, nr - nl + 1, v - segMax[i], 0, v - segMax[i], 0);
    }
    else {
        down(i, nl, nr);
        int mid = (nl + nr) >> 1;
        if (l <= mid) updateMin(l, r, v, nl, mid, i << 1);
        if (r > mid)  updateMin(l, r, v, mid + 1, nr, i << 1 | 1);
        up(i);
    }
}

ll querySum(int l, int r, int nl, int nr, int i) {
    if (l <= nl && nr <= r) return segSum[i];
    down(i, nl, nr);
    int mid = (nl + nr) >> 1;
    ll res = 0;
    if (l <= mid) res += querySum(l, r, nl, mid, i << 1);
    if (r > mid)  res += querySum(l, r, mid + 1, nr, i << 1 | 1);
    return res;
}

ll queryMax(int l, int r, int nl, int nr, int i) {
    if (l <= nl && nr <= r) return segMax[i];
    down(i, nl, nr);
    int mid = (nl + nr) >> 1;
    ll res = NEG_INF;
    if (l <= mid) res = max(res, queryMax(l, r, nl, mid, i << 1));
    if (r > mid)  res = max(res, queryMax(l, r, mid + 1, nr, i << 1 | 1));
    return res;
}

ll queryHist(int l, int r, int nl, int nr, int i) {
    if (l <= nl && nr <= r) return segMaxHist[i];
    down(i, nl, nr);
    int mid = (nl + nr) >> 1;
    ll res = NEG_INF;
    if (l <= mid) res = max(res, queryHist(l, r, nl, mid, i << 1));
    if (r > mid)  res = max(res, queryHist(l, r, mid + 1, nr, i << 1 | 1));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    arr.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    segSum.assign(4 * n + 4, 0);
    segMax.assign(4 * n + 4, 0);
    segSem.assign(4 * n + 4, NEG_INF);
    segMaxAdd.assign(4 * n + 4, 0);
    segOAdd.assign(4 * n + 4, 0);
    segMaxHist.assign(4 * n + 4, 0);
    segMaxAddHist.assign(4 * n + 4, 0);
    segOAddHist.assign(4 * n + 4, 0);
    segCnt.assign(4 * n + 4, 0);

    build(1, n, 1);
    while (m--) {
        int op, l, r;
        ll v;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> v;
            updateAdd(l, r, v, 1, n, 1);
        }
        else if (op == 2) {
            cin >> v;
            updateMin(l, r, v, 1, n, 1);
        }
        else if (op == 3) {
            cout << querySum(l, r, 1, n, 1) << '\n';
        }
        else if (op == 4) {
            cout << queryMax(l, r, 1, n, 1) << '\n';
        }
        else {
            cout << queryHist(l, r, 1, n, 1) << '\n';
        }
    }
    return 0;
}
