#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
class CountIntervals {
public:
    int n;
    int cnt;
    vector<ll>l;
    vector<ll>r;
    vector<ll>sum;
    vector<ll>addtion;
    CountIntervals() {
        n = 1e9;
        l.assign(900001, 0);
        r.assign(900001, 0);
        sum.assign(900001, 0);
        addtion.assign(900001, 0);
        cnt = 1;
    }
    void lazy(int i, int v, int n) {
        sum[i] = v * n;
        addtion[i] = v;
    }
    void down(int i, int a, int b) {
        int mid = a + (b - a) / 2;
        if (l[i] == 0)l[i] = ++cnt;
        if (r[i] == 0)r[i] = ++cnt;
        lazy(l[i], addtion[i], mid - a + 1);
        lazy(r[i], addtion[i], b - mid);
        addtion[i] = 0;
    }
    void update(int left, int right, int v, int a, int b, int i) {
        int mid = a + (b - a) / 2;
        if (sum[i] == b - a + 1)return;
        if (left <= a && right >= b) {
            lazy(i, v, b - a + 1);
        }
        if (addtion[i])down(i, a, b);
        if (left <= mid) {
            if (l[i] == 0)l[i] = ++cnt;
            update(left, right, v, a, mid, l[i]);
        }
        if (right > mid) {
            if (r[i] == 0)r[i] = ++cnt;
            update(left, right, v, mid + 1, b, r[i]);
        }
        sum[i] = sum[l[i]] + sum[r[i]];
    }
    void add(int left, int right) {
        update(left, right, 1, 1, n, 1);
    }

    int count() {
        return sum[1];
    }
};
