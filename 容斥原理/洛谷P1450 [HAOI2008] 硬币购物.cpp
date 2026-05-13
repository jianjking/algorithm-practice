#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll f(const vector<ll>& cnt, const vector<ll>& value, const vector<ll>& arr, ll s) {
    ll sum = 0;
    // 枚举 1 到 15 的子集掩码
    for (ll mask = 1; mask < 16; mask++) {
        ll sign = -1;
        ll tmp = mask;
        ll t = s;
        // 遍历 4 种硬币
        for (int j = 0; j < 4 && tmp > 0; ++j, tmp >>= 1) {
            if (tmp & 1) {
                // 容斥：减去 (cnt[j]+1) 件硬币 j 的所有组合数
                t -= value[j] * (cnt[j] + 1);
                sign = -sign;
            }
        }
        if (t >= 0) {
            sum += sign * arr[t];
        }
    }
    // 全集减去所有「漏掉至少一种硬币上限」的组合
    return arr[s] - sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> value(4);
    ll n_queries;
    // 读入 4 种硬币面值
    for (int i = 0; i < 4; i++) {
        cin >> value[i];
    }
    // 读入询问次数
    cin >> n_queries;

    // 预处理：完全背包，arr[x] = 用无限制硬币凑成 x 的方法数
    const int MAXS = 100000;
    vector<ll> arr(MAXS + 1, 0);
    arr[0] = 1;
    for (int i = 0; i < 4; i++) {
        ll c = value[i];
        for (ll j = c; j <= MAXS; j++) {
            arr[j] += arr[j - c];
        }
    }

    // 处理每次查询
    while (n_queries--) {
        vector<ll> cnt(4);
        ll s;
        cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3] >> s;
        cout << f(cnt, value, arr, s) << "\n";
    }

    return 0;
}
