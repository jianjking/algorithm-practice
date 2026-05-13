#include <iostream>
#include <vector>
using namespace std;

vector<long long> sum;
vector<long long> add;

void dfs(vector<long long>& tmp, int l, int r, int i) {
    if (l == r) {
        sum[i] = tmp[l];
    }
    else {
        int mid = l + (r - l) / 2;
        dfs(tmp, l, mid, 2 * i);
        dfs(tmp, mid + 1, r, 2 * i + 1);
        sum[i] = sum[2 * i] + sum[2 * i + 1];
    }
}

void lazy(int i, long long v, int n) {
    add[i] += v;
    sum[i] += (long long)n * v;
}

void down(int i, int l, int r) {
    int mid = l + (r - l) / 2;
    lazy(2 * i, add[i], mid - l + 1);
    lazy(2 * i + 1, add[i], r - mid);
    add[i] = 0;
}

void addtion(int a, int b, int c, int d, int i, long long v) {
    if (a <= c && b >= d) {
        lazy(i, v, d - c + 1);
    }
    else {
        int mid = c + (d - c) / 2;
        if (add[i] != 0) {
            down(i, c, d);
        }
        if (a <= mid) addtion(a, b, c, mid, 2 * i, v);
        if (b > mid) addtion(a, b, mid + 1, d, 2 * i + 1, v);
        sum[i] = sum[2 * i] + sum[2 * i + 1];
    }
}

long long query(int a, int b, int c, int d, int i) {
    if (a <= c && b >= d) return sum[i];
    if (add[i] != 0) {
        down(i, c, d);
    }
    long long ans = 0;
    int mid = c + (d - c) / 2;
    if (a <= mid) ans += query(a, b, c, mid, 2 * i);
    if (b > mid) ans += query(a, b, mid + 1, d, 2 * i + 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    sum.assign(4 * n + 1, 0);
    add.assign(4 * n + 1, 0);

    vector<long long> nums(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
    }

    vector<long long> tmp(n + 1);
    tmp[1] = nums[1];
    for (int i = 2; i <= n; ++i) {
        tmp[i] = nums[i] - nums[i - 1];
    }
    dfs(tmp, 1, n, 1);

    for (int i = 0; i < m; ++i) {
        int p;
        cin >> p;
        if (p == 1) {
            int a, b;
            long long c, d;
            cin >> a >> b >> c >> d;
            // 在 a 处加首项 c
            addtion(a, a, 1, n, 1, c);
            // 在 [a+1, b] 处加公差 d
            if (a + 1 <= b) addtion(a + 1, b, 1, n, 1, d);
            // 在 b+1 处减去累加量 c + (b - a) * d
            if (b < n) addtion(b + 1, b + 1, 1, n, 1, -(c + (long long)(b - a) * d));
        }
        else {
            int a;
            cin >> a;
            cout << query(1, a, 1, n, 1) << '\n';
        }
    }
    return 0;
}
