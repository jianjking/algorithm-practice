#include <cstdio>
#include <vector>
#include <limits>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long;
vector<ll> add, mult, sum;
int mod;

void addlazy(int l, int r, int k, int nums) {
    k %= mod;
    add[nums] = (add[nums] + k) % mod;
    // 用 64 位计算长度*增量，并把 sum 自身也取模
    ll len = (r - l + 1) % mod;
    sum[nums] = (sum[nums] + len * k) % mod;
}

void multlazy(int k, int nums) {
    k %= mod;
    add[nums] = (add[nums] * k) % mod;
    sum[nums] = (sum[nums] * k) % mod;
    mult[nums] = (mult[nums] * k) % mod;
}

void down(int l, int r, int nums) {
    if (l == r) return; // 叶子不下推
    int mid = l + (r - l) / 2;
    if (mult[nums] != 1) {
        multlazy(mult[nums], 2 * nums);
        multlazy(mult[nums], 2 * nums + 1);
        mult[nums] = 1;
    }
    if (add[nums] != 0) {
        addlazy(l, mid, add[nums], 2 * nums);
        addlazy(mid + 1, r, add[nums], 2 * nums + 1);
        add[nums] = 0;
    }
}

void up(int nums) {
    sum[nums] = (sum[2 * nums] + sum[2 * nums + 1]) % mod;
}

void addtion(int x, int y, int l, int r, int k, int nums) {
    if (y < l || r < x) return;            // 无交集剪枝
    if (x <= l && y >= r) { addlazy(l, r, k, nums); return; }
    down(l, r, nums);
    int mid = l + (r - l) / 2;
    if (x <= mid) addtion(x, y, l, mid, k, 2 * nums);
    if (y > mid) addtion(x, y, mid + 1, r, k, 2 * nums + 1);
    up(nums);
}

void multipy(int x, int y, int l, int r, int k, int nums) {
    if (y < l || r < x) return;            // 无交集剪枝
    if (x <= l && y >= r) { multlazy(k, nums); return; }
    down(l, r, nums);
    int mid = l + (r - l) / 2;
    if (x <= mid) multipy(x, y, l, mid, k, 2 * nums);
    if (y > mid) multipy(x, y, mid + 1, r, k, 2 * nums + 1);
    up(nums);
}

int query(int x, int y, int l, int r, int nums) {
    if (y < l || r < x) return 0;          // 无交集剪枝
    if (x <= l && y >= r) return sum[nums] % mod;
    down(l, r, nums);
    ll ans = 0;
    int mid = l + (r - l) / 2;
    if (x <= mid) ans = (ans + query(x, y, l, mid, 2 * nums)) % mod;
    if (y > mid) ans = (ans + query(x, y, mid + 1, r, 2 * nums + 1)) % mod;
    return (int)ans;
}

void build(int x, int y, int nums, vector<int>& num) {
    if (x == y) {
        sum[nums] = ((num[x - 1] % mod) + mod) % mod; // 初值进模域
        return;
    }
    int mid = x + (y - x) / 2;
    build(x, mid, 2 * nums, num);
    build(mid + 1, y, 2 * nums + 1, num);
    up(nums);
}

int main() {
    int n, q;
    scanf("%d%d%d", &n, &q, &mod);
    add.assign(4 * n + 5, 0);   // 开大，避免擦边
    mult.assign(4 * n + 5, 1);
    sum.assign(4 * n + 5, 0);
    vector<int> num(n);
    for (int i = 0; i < n; i++) scanf("%d", &num[i]);
    build(1, n, 1, num);
    for (int i = 0; i < q; i++) {
        int op; scanf("%d", &op);
        if (op == 2) {
            int x, y, k; scanf("%d%d%d", &x, &y, &k);
            addtion(x, y, 1, n, k, 1);
        }
        else if (op == 1) {
            int x, y, k; scanf("%d%d%d", &x, &y, &k);
            multipy(x, y, 1, n, k, 1);
        }
        else {
            int x, y; scanf("%d%d", &x, &y);
            printf("%d\n", query(x, y, 1, n, 1));
        }
    }
    return 0;
}
