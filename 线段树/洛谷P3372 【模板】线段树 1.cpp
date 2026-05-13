#include <iostream>
#include <vector>
using namespace std;

vector<long long> sum;
vector<long long> add;

// 在节点 idx 上对长度为 len 的区间增加 val
void lazy(int idx, int len, long long val) {
    sum[idx] += val * len;
    add[idx] += val;
}

// 把当前节点的懒标记推到两个子节点
void down(long long val, int leftLen, int rightLen, int idx) {
    lazy(idx * 2, leftLen, val);
    lazy(idx * 2 + 1, rightLen, val);
}

void dfs(int l, int r, const vector<long long>& nums, int idx) {
    if (l == r) {
        sum[idx] = nums[l];
    }
    else {
        int mid = l + (r - l) / 2;
        dfs(l, mid, nums, idx * 2);
        dfs(mid + 1, r, nums, idx * 2 + 1);
        sum[idx] = sum[idx * 2] + sum[idx * 2 + 1];
    }
}

long long query(int ql, int qr, int l, int r, int idx) {
    if (ql <= l && r <= qr) {
        return sum[idx];
    }
    int mid = l + (r - l) / 2;
    // 下推并清零
    if (add[idx] != 0) {
        down(add[idx], mid - l + 1, r - mid, idx);
        add[idx] = 0;
    }
    long long ans = 0;
    if (ql <= mid)      ans += query(ql, qr, l, mid, idx * 2);
    if (qr > mid)      ans += query(ql, qr, mid + 1, r, idx * 2 + 1);
    return ans;
}

void addtion(int ql, int qr, long long val, int l, int r, int idx) {
    if (ql <= l && r <= qr) {
        lazy(idx, r - l + 1, val);
    }
    else {
        int mid = l + (r - l) / 2;
        // 下推并清零
        if (add[idx] != 0) {
            down(add[idx], mid - l + 1, r - mid, idx);
            add[idx] = 0;
        }
        if (ql <= mid) addtion(ql, qr, val, l, mid, idx * 2);
        if (qr > mid) addtion(ql, qr, val, mid + 1, r, idx * 2 + 1);
        sum[idx] = sum[idx * 2] + sum[idx * 2 + 1];
    }
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

    sum.assign(4 * n, 0LL);
    add.assign(4 * n, 0LL);

    dfs(1, n, nums, 1);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int L, R;
            long long v;
            cin >> L >> R >> v;
            addtion(L, R, v, 1, n, 1);
        }
        else {
            int L, R;
            cin >> L >> R;
            cout << query(L, R, 1, n, 1) << "\n";
        }
    }
    return 0;
}
