#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

vector<long long> addt, mx, sett;
vector<bool> vis;

void dfs(int l, int r, vector<long long>& nums, int i) {
    if (l == r) {
        mx[i] = nums[l];
    }
    else {
        int mid = (l + r) >> 1;
        dfs(l, mid, nums, 2 * i);
        dfs(mid + 1, r, nums, 2 * i + 1);
        mx[i] = max(mx[2 * i], mx[2 * i + 1]);
    }
}

void apply_add(long long v, int i) {
    addt[i] += v;
    mx[i] += v;
}

void apply_set(long long v, int i) {
    sett[i] = v;
    mx[i] = v;
    addt[i] = 0;
    vis[i] = true;
}

void push_down(int i) {
    if (vis[i]) {
        apply_set(sett[i], 2 * i);
        apply_set(sett[i], 2 * i + 1);
        vis[i] = false;
    }
    if (addt[i] != 0) {
        apply_add(addt[i], 2 * i);
        apply_add(addt[i], 2 * i + 1);
        addt[i] = 0;
    }
}

void range_add(int a, int b, long long v, int l, int r, int i) {
    if (r < a || l > b) return;
    if (l >= a && r <= b) {
        apply_add(v, i);
    }
    else {
        int mid = (l + r) >> 1;
        push_down(i);
        range_add(a, b, v, l, mid, 2 * i);
        range_add(a, b, v, mid + 1, r, 2 * i + 1);
        mx[i] = max(mx[2 * i], mx[2 * i + 1]);
    }
}

void range_set(int a, int b, long long v, int l, int r, int i) {
    if (r < a || l > b) return;
    if (l >= a && r <= b) {
        apply_set(v, i);
    }
    else {
        int mid = (l + r) >> 1;
        push_down(i);
        range_set(a, b, v, l, mid, 2 * i);
        range_set(a, b, v, mid + 1, r, 2 * i + 1);
        mx[i] = max(mx[2 * i], mx[2 * i + 1]);
    }
}

long long query(int a, int b, int l, int r, int i) {
    if (r < a || l > b) return -INF;
    if (l >= a && r <= b) {
        return mx[i];
    }
    int mid = (l + r) >> 1;
    push_down(i);
    long long left = query(a, b, l, mid, 2 * i);
    long long right = query(a, b, mid + 1, r, 2 * i + 1);
    return max(left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> nums(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    addt.assign(4 * n, 0);
    mx.assign(4 * n, 0);
    sett.assign(4 * n, 0);
    vis.assign(4 * n, false);

    dfs(1, n, nums, 1);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            long long c;
            cin >> a >> b >> c;
            range_set(a, b, c, 1, n, 1);
        }
        else if (op == 2) {
            int a, b;
            long long c;
            cin >> a >> b >> c;
            range_add(a, b, c, 1, n, 1);
        }
        else {  // op == 3
            int a, b;
            cin >> a >> b;
            cout << query(a, b, 1, n, 1) << "\n";
        }
    }

    return 0;
}